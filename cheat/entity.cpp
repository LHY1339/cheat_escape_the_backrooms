#include "entity.h"

#include "gvalue.h"

SDK::APawn* last_pawn = nullptr;
SDK::APawn* control_entity = nullptr;

void entity::init()
{
}

void entity::main()
{
	__try
	{
		if (!control_entity || !gvalue::world || !gvalue::controller)
		{
			control_entity = nullptr;
			return;
		}

		SDK::FVector fwd = SDK::UKismetMathLibrary::GetForwardVector(control_entity->GetControlRotation());
		SDK::FVector right = SDK::UKismetMathLibrary::GetRightVector(control_entity->GetControlRotation());

		if (GetAsyncKeyState('W') & 0x8000)
		{
			control_entity->AddMovementInput(fwd, 1.0f, true);
		}
		if (GetAsyncKeyState('S') & 0x8000)
		{
			control_entity->AddMovementInput(fwd, -1.0f, true);
		}
		if (GetAsyncKeyState('A') & 0x8000)
		{
			control_entity->AddMovementInput(right, -1.0f, true);
		}
		if (GetAsyncKeyState('D') & 0x8000)
		{
			control_entity->AddMovementInput(right, 1.0f, true);
		}

		control_entity->AddControllerPitchInput(gvalue::y_offset * 0.5);
		control_entity->AddControllerYawInput(gvalue::x_offset * 0.5);
		gvalue::y_offset = 0.0f;
		gvalue::x_offset = 0.0f;
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		control_entity = nullptr;
		printf("control_entity error\n");
	}
}

void entity::kill_all()
{
	SDK::TArray<SDK::AActor*> list;
	SDK::UGameplayStatics::GetAllActorsOfClass(gvalue::world, SDK::ACharacter::StaticClass(), &list);
	for (SDK::AActor* actor : list)
	{
		if (actor->IsA(SDK::ABP_Explorer_C::StaticClass()) || actor->IsA(SDK::ABPCharacter_Demo_C::StaticClass()))
		{
			continue;
		}
		actor->K2_DestroyActor();
	}
}

void entity::kill(const std::string& name)
{
	SDK::TArray<SDK::AActor*> list;
	SDK::UGameplayStatics::GetAllActorsOfClass(gvalue::world, SDK::ACharacter::StaticClass(), &list);
	for (SDK::AActor* actor : list)
	{
		if (actor->Class->Name.ToString() == name)
		{
			actor->K2_DestroyActor();
		}
	}
}

void entity::spawn(SDK::TSubclassOf<SDK::AActor> cls)
{
	if (!gvalue::world || !gvalue::controller)
	{
		return;
	}
	SDK::FVector trace_start = gvalue::controller->PlayerCameraManager->GetCameraLocation();
	SDK::FVector trace_end = trace_start + SDK::UKismetMathLibrary::GetForwardVector(gvalue::controller->GetControlRotation()) * 2000;
	SDK::TArray<SDK::AActor*> ignore_actors;
	ignore_actors.Add(gvalue::controller->Pawn);
	SDK::FHitResult result;
	SDK::UKismetSystemLibrary::LineTraceSingle(
		gvalue::world,
		trace_start,
		trace_end,
		SDK::ETraceTypeQuery::TraceTypeQuery1,
		false,
		ignore_actors,
		SDK::EDrawDebugTrace::None,
		&result,
		true,
		SDK::FLinearColor(1.0f, 0.0f, 0.0f, 1.0f),
		SDK::FLinearColor(0.0f, 1.0f, 0.0f, 1.0f),
		0.0f
	);

	SDK::FVector location = result.bBlockingHit ? result.Location : result.TraceEnd;
	SDK::FTransform trans;
	trans.Translation = location;
	trans.Scale3D = SDK::FVector(1.0f, 1.0f, 1.0f);

	SDK::AActor* new_actor = SDK::UGameplayStatics::BeginDeferredActorSpawnFromClass(
		gvalue::world,
		cls,
		trans,
		SDK::ESpawnActorCollisionHandlingMethod::AlwaysSpawn,
		nullptr
	);
	if (new_actor)
	{
		SDK::UGameplayStatics::FinishSpawningActor(new_actor, trans);
	}
}

void entity::poss(SDK::APawn* pawn)
{
	if (!gvalue::world || !gvalue::controller)
	{
		return;
	}
	if (gvalue::controller->Pawn->IsA(SDK::ABPCharacter_Demo_C::StaticClass()))
	{
		last_pawn = gvalue::controller->Pawn;
	}
	gvalue::controller->Possess(pawn);
	control_entity = pawn;
}

void entity::unposs()
{
	if (!last_pawn)
	{
		return;
	}
	gvalue::controller->Possess(last_pawn);
	control_entity = nullptr;
	last_pawn = nullptr;
}
