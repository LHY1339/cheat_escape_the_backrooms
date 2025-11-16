#include "item.h"

#include "gvalue.h"

void item::spawn(SDK::TSubclassOf<SDK::AActor> actor_class)
{
    if (!gvalue::world || !gvalue::controller)
    {
        return;
    }

    if (!gvalue::controller->Pawn || !gvalue::controller->Pawn->IsA(SDK::ABPCharacter_Demo_C::StaticClass()))
    {
        return;
    }

    SDK::ABPCharacter_Demo_C* my_player = static_cast<SDK::ABPCharacter_Demo_C*>(gvalue::controller->Pawn);

    SDK::FTransform trans;
    trans.Translation = gvalue::controller->PlayerCameraManager->GetCameraLocation();
    SDK::AActor* new_actor = SDK::UGameplayStatics::BeginDeferredActorSpawnFromClass(
        gvalue::world,
        actor_class,
        trans,
        SDK::ESpawnActorCollisionHandlingMethod::AlwaysSpawn,
        nullptr
    );
    SDK::UGameplayStatics::FinishSpawningActor(new_actor, trans);
    SDK::ABP_DroppedItem_C* item = static_cast<SDK::ABP_DroppedItem_C*>(new_actor);
    my_player->InvAdd(item);
}