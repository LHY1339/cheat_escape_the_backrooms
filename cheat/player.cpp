#include "player.h"

#include "gvalue.h"
#include "_sdk.h"

SDK::ABPCharacter_Demo_C* my_player = nullptr;
SDK::AMP_PS_C* my_state = nullptr;

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
		return;
	}
	if (!gvalue::controller->PlayerState || !gvalue::controller->PlayerState->IsA(SDK::AMP_PS_C::StaticClass()))
	{
		my_state = nullptr;
		return;
	}
	my_player = static_cast<SDK::ABPCharacter_Demo_C*>(gvalue::controller->Pawn);
	my_state = static_cast<SDK::AMP_PS_C*>(gvalue::controller->PlayerState);
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

}
