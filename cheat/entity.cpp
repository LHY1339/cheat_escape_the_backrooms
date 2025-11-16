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
