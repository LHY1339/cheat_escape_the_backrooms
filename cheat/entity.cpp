#include "entity.h"

#include "gvalue.h"

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
	SDK::FVector trace_end = trace_start + SDK::UKismetMathLibrary::GetForwardVector(gvalue::controller->GetControlRotation()) * 1000;
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