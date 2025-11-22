#include "player.h"

#include "gvalue.h"
#include "_sdk.h"
#include "render.h"

SDK::ABPCharacter_Demo_C* my_player = nullptr;
SDK::AMP_PS_C* my_state = nullptr;
float def_sensitivity = -1;
SDK::FVector fly_location = SDK::FVector(-114514, -114514, -114514);

void player::init()
{

}

void player::main()
{
	if (!gvalue::world || !gvalue::controller)
	{
		return;
	}
	get_player();
}

void player::get_player()
{

	if (!gvalue::controller->Pawn || !gvalue::controller->Pawn->IsA(SDK::ABPCharacter_Demo_C::StaticClass()))
	{
		my_player = nullptr;
		def_sensitivity = -1;
		fly_location = SDK::FVector(-114514, -114514, -114514);
		return;
	}
	if (!gvalue::controller->PlayerState || !gvalue::controller->PlayerState->IsA(SDK::AMP_PS_C::StaticClass()))
	{
		my_state = nullptr;
		def_sensitivity = -1;
		fly_location = SDK::FVector(-114514, -114514, -114514);
		return;
	}
	my_player = static_cast<SDK::ABPCharacter_Demo_C*>(gvalue::controller->Pawn);
	my_state = static_cast<SDK::AMP_PS_C*>(gvalue::controller->PlayerState);
	if (def_sensitivity == -1)
	{
		def_sensitivity = my_player->MouseSensitivity;
	}
	property();
}

void player::property()
{
	if (gvalue::inf_stamina)
	{
		my_player->Stamina = 45.0f;
	}

	if (gvalue::no_balance)
	{
		my_player->BalanceTimeline->TheTimeline.Position = 0.0f;
	}

	if (gvalue::inf_sanity)
	{
		my_state->Sanity = my_state->MaxSanity;
	}

	if (gvalue::inf_jump)
	{
		my_player->JumpCurrentCount = 0;
		my_player->JumpMaxCount = 2;
	}
	else
	{
		my_player->JumpMaxCount = 1;
	}

	if (my_player->IsSprinting)
	{
		my_player->CharacterMovement->MaxWalkSpeed = gvalue::run_speed;
	}
	else
	{
		my_player->CharacterMovement->MaxWalkSpeed = gvalue::walk_speed;
	}

	if (my_player->SprintSpeed != gvalue::run_speed)
	{
		my_player->SprintSpeed = gvalue::run_speed;
		my_player->SetSprintSpeedServer(gvalue::run_speed);
	}

	if (my_player->WalkSpeed != gvalue::walk_speed)
	{
		my_player->WalkSpeed = gvalue::walk_speed;
		my_player->SetWalkSpeedServer(gvalue::walk_speed);
	}

	if (my_player->CrouchWalkSpeed != gvalue::crouch_speed)
	{
		my_player->CrouchWalkSpeed = gvalue::crouch_speed;
		my_player->SetCrouchWalkSpeedServer(gvalue::crouch_speed);
	}

	my_player->CustomTimeDilation = gvalue::speedup_multi;
	my_player->MouseSensitivity = def_sensitivity / gvalue::speedup_multi;

	my_player->SetReplicateMovement(!gvalue::ghost_mode);

	if (fly_location == SDK::FVector(-114514, -114514, -114514))
	{
		fly_location = my_player->K2_GetActorLocation();
	}

	if (gvalue::fly_mode)
	{
		const SDK::FRotator con_rot = my_player->GetControlRotation();
		const SDK::FRotator act_rot = my_player->K2_GetActorRotation();

		if (GetAsyncKeyState('W') & 0x8000)
		{
			fly_location += SDK::UKismetMathLibrary::GetForwardVector(con_rot) * gvalue::fly_speed;
		}
		if (GetAsyncKeyState('S') & 0x8000)
		{
			fly_location += SDK::UKismetMathLibrary::GetForwardVector(con_rot) * -1 * gvalue::fly_speed;
		}
		if (GetAsyncKeyState('A') & 0x8000)
		{
			fly_location += SDK::UKismetMathLibrary::GetRightVector(con_rot) * -1 * gvalue::fly_speed;
		}
		if (GetAsyncKeyState('D') & 0x8000)
		{
			fly_location += SDK::UKismetMathLibrary::GetRightVector(con_rot) * gvalue::fly_speed;
		}
		if (GetAsyncKeyState(VK_SPACE) & 0x8000)
		{
			fly_location += SDK::UKismetMathLibrary::GetUpVector(act_rot) * gvalue::fly_speed;
		}
		if (GetAsyncKeyState(VK_CONTROL) & 0x8000)
		{
			fly_location += SDK::UKismetMathLibrary::GetUpVector(act_rot) * -1 * gvalue::fly_speed;
		}
		
		my_player->K2_SetActorLocation(fly_location, false, nullptr, true);
	}
	else
	{
		fly_location = my_player->K2_GetActorLocation();
	}

	if (gvalue::x_delete)
	{
		SDK::FVector trace_start = gvalue::controller->PlayerCameraManager->GetCameraLocation();
		SDK::FVector trace_end = trace_start + SDK::UKismetMathLibrary::GetForwardVector(my_player->GetControlRotation()) * 10000;
		SDK::TArray<SDK::AActor*> ignore_actors;
		ignore_actors.Add(my_player);
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

		SDK::AActor* del_actor = nullptr;
		if (result.bBlockingHit)
		{
			draw_extent(result.Actor.Get(), SDK::FLinearColor(1.0f, 0.2f, 0.0f, 1.0f), SDK::UKismetStringLibrary::Conv_NameToString(result.Actor.Get()->Name).ToWString());
			del_actor = result.Actor.Get();
		}

		static bool x_down = false;
		if (GetAsyncKeyState('X') & 0x8000)
		{
			if (!x_down)
			{
				if (del_actor)
				{
					result.Actor.Get()->K2_DestroyActor();
				}
				x_down = true;
			}
		}
		else
		{
			x_down = false;
		}
	}
}

void player::draw_extent(SDK::AActor* actor, const SDK::FLinearColor& color, const std::wstring& name)
{
	if (!actor)
	{
		return;
	}

	struct line_01
	{
		SDK::FVector2D p1;
		SDK::FVector2D p2;
	};

	SDK::FVector origin, extent;
	actor->GetActorBounds(true, &origin, &extent, true);
	const SDK::FVector point[] =
	{
		origin + SDK::FVector(extent.X, extent.Y, extent.Z),        //0
		origin + SDK::FVector(-extent.X, -extent.Y, -extent.Z),     //1
		origin + SDK::FVector(extent.X, -extent.Y, extent.Z),       //2
		origin + SDK::FVector(extent.X, extent.Y, -extent.Z),       //3
		origin + SDK::FVector(extent.X, -extent.Y, -extent.Z),      //4
		origin + SDK::FVector(-extent.X, extent.Y, extent.Z),       //5
		origin + SDK::FVector(-extent.X, extent.Y, -extent.Z),      //6
		origin + SDK::FVector(-extent.X, -extent.Y, extent.Z)       //7
	};

	SDK::FVector2D point_2d[8];
	for (int i = 0; i < 8; i++)
	{
		SDK::FVector2D ori_2d;
		bool in_view = gvalue::controller->ProjectWorldLocationToScreen(point[i], &ori_2d, true);
		if (!in_view)
		{
			ori_2d = SDK::FVector2D(-114514, -114514);
		}
		point_2d[i] = ori_2d;
	}

	const line_01 line[12] =
	{
		{point_2d[0],point_2d[2]},
		{point_2d[0],point_2d[3]},
		{point_2d[0],point_2d[5]},

		{point_2d[1],point_2d[4]},
		{point_2d[1],point_2d[6]},
		{point_2d[1],point_2d[7]},

		{point_2d[2],point_2d[4]},
		{point_2d[2],point_2d[7]},

		{point_2d[3],point_2d[4]},
		{point_2d[3],point_2d[6]},

		{point_2d[5],point_2d[6]},
		{point_2d[5],point_2d[7]}
	};

	for (int i = 0; i < 12; i++)
	{
		if (line[i].p1 == SDK::FVector2D(-114514, -114514) ||
			line[i].p2 == SDK::FVector2D(-114514, -114514))
		{
			continue;
		}
		render::draw_line(
			line[i].p1,
			line[i].p2,
			1.0f,
			color
		);
	}

	SDK::FVector2D ori_2d;
	bool in_view = gvalue::controller->ProjectWorldLocationToScreen(origin, &ori_2d, true);
	if (in_view)
	{
		const std::wstring str = L"[X¼ü] É¾³ý " + name;
		render::draw_text(
			gvalue::engine->MediumFont,
			str.c_str(),
			ori_2d,
			SDK::FVector2D(1.0f, 1.0f),
			color,
			1.0f,
			SDK::FLinearColor(0.0f, 0.0f, 0.0f, 0.0f),
			SDK::FVector2D(0.0f, 0.0f),
			false,
			false,
			false,
			SDK::FLinearColor(0.0f, 0.0f, 0.0f, 0.0f)
		);
	}
}
