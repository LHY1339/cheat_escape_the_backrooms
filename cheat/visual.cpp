#include "visual.h"

#include "_sdk.h"
#include "gvalue.h"
#include "render.h"

#include <unordered_map>

std::unordered_map<std::wstring, std::wstring> name_map;

void visual::init()
{
    name_map[L"Juice"] = L"果汁";
    name_map[L"AlmondWater"] = L"杏仁水";
    name_map[L"Flashlight"] = L"手电筒";
    name_map[L"LiquidPain"] = L"液态痛苦";
    name_map[L"EnergyBar"] = L"能量棒";
    name_map[L"LiquidPain"] = L"液态痛苦";
    name_map[L"DivingHelmet"] = L"潜水头盔";
    name_map[L"DivingHelmet"] = L"潜水头盔";
    name_map[L"Flaregun"] = L"信号枪";
    name_map[L"Rope"] = L"绳子";
    name_map[L"WalkieTalkie"] = L"对讲机";
    name_map[L"Chainsaw"] = L"电锯";
    name_map[L"Ticket"] = L"小票";
    name_map[L"玩家"] = L"玩家";
    name_map[L"ChainsawFast"] = L"快速电锯";
    name_map[L"Firework"] = L"烟花";
    name_map[L"GlowstickYellow"] = L"黄色荧光棒";
    name_map[L"GlowstickRed"] = L"红色荧光棒";
    name_map[L"GlowstickBlue"] = L"蓝色荧光棒";
    name_map[L"GlowStick"] = L"荧光棒";
    name_map[L"GlowStick"] = L"荧光棒";

    name_map[L"BP_Note_C"] = L"笔记";
    name_map[L"BP_MEGDoor_C"] = L"门";
    name_map[L"BP_SchoolDoors_C"] = L"门";
    name_map[L"BP_HubDoor2_C"] = L"门";
    name_map[L"BP_LabDoor_C"] = L"门";
    name_map[L"BP_SmallDoor_C"] = L"门";
    name_map[L"BP_188_Door_C"] = L"门";
    name_map[L"BP_Door_Master_C"] = L"门";
    name_map[L"BP_Elevator_Button_Bunker_C"] = L"电梯按钮";
    name_map[L"BP_Window_C"] = L"窗户";
    name_map[L"BP_DivingGear_C"] = L"潜水装备";
    name_map[L"BP_Ladder_C"] = L"梯子";
    name_map[L"BP_LadderPiece_C"] = L"梯子碎片";
    name_map[L"BP_LadderDoor_C"] = L"门";
    name_map[L"BP_Vent_C"] = L"通风口";
    name_map[L"BP_button_C"] = L"按钮";
    name_map[L"BP_GarageDoor_C"] = L"门";
    name_map[L"BP_Closet_Garage_C"] = L"柜子";
    name_map[L"BP_GarageDoor_C"] = L"门";
    name_map[L"BP_KeyPiece_C"] = L"钥匙";
    name_map[L"BP_KeyTurn_C"] = L"钥匙孔";
    name_map[L"BP_ElevatorButton_C"] = L"电梯按钮";
    name_map[L"BP_DoubleDoor_C"] = L"门";
    name_map[L"BP_Cabinet_C"] = L"柜子";
    name_map[L"BP_BoilerDoor_C"] = L"门";
    name_map[L"BP_IndustrialDoor_2_C"] = L"门";
    name_map[L"BP_metaldoors_C"] = L"门";
    name_map[L"BP_LockedDoor_C"] = L"门";
    name_map[L"BP_OfficeDoor_C"] = L"门";
    name_map[L"BP_ConnectorValve_C"] = L"阀门";
    name_map[L"BP_Elevator_Cave_C"] = L"电梯";
    name_map[L"BP_PlankWall_C"] = L"木板墙";
    name_map[L"BP_ShadowLight_Switch_C"] = L"电灯开关";
    name_map[L"BP_Locker_3_C"] = L"柜子";
    name_map[L"BP_Plank_Door_C"] = L"门";
    name_map[L"BP_Timed_Lever_C"] = L"任务";
    name_map[L"BP_ExitDoor_C"] = L"门";
    name_map[L"BP_EndingsDoor_C"] = L"门";
    name_map[L"BP_Elevator_Button_Hub_C"] = L"电梯按钮";
    name_map[L"BP_Final_Ending_Arcade_C"] = L"结局游戏机";
    name_map[L"BP_Connected_Door_C"] = L"门";
    name_map[L"BP_Gate_Lever_C"] = L"门";
    name_map[L"BP_Blueprint_C"] = L"蓝图";
    name_map[L"BP_Blue_Door_C"] = L"门";
    name_map[L"BP_Dash_Lever_C"] = L"仪表板";
    name_map[L"BP_188_Elevator_Button_C"] = L"电梯按钮";
    name_map[L"BP_Pushable_C"] = L"电视";
    name_map[L"BP_188_Lobby_Doors_C"] = L"门";
    name_map[L"BP_YouCheated_Door_C"] = L"门：你作弊了";
    name_map[L"BP_Pool_Valve_C"] = L"阀门";
    name_map[L"BP_Raft_Passengers_C"] = L"皮划艇";
    name_map[L"BP_Fun_Single_Door_C"] = L"门";
    name_map[L"BP_Fun_Double_Door_C"] = L"门";
    name_map[L"BP_FunKey_C"] = L"钥匙";
    name_map[L"BP_Balloons_Key_C"] = L"钥匙";

    name_map[L"BP_RoamingPartygoer_Idle_C"] = L"派对客";
    name_map[L"BP_RoamingPartygoer_C"] = L"派对客";
    name_map[L"BP_Partypooper_C"] = L"扫兴客";
    name_map[L"Bacteria_BP_C"] = L"细菌";
    name_map[L"BP_SkinStealer_C"] = L"窃皮者";
    name_map[L"Smiler_BP2_C"] = L"笑魇";
    name_map[L"BP_Roaming_Smiler_C"] = L"笑魇";
    name_map[L"BP_Smiler_Dash_C"] = L"笑魇";
    name_map[L"BP_SkinStealer_Cave_C"] = L"窃皮者";
    name_map[L"BP_Cave_Moth_C"] = L"死亡飞蛾";
    name_map[L"Bacteria_Roaming_BP_C"] = L"细菌";
    name_map[L"BP_SkinStealer_Level07_C"] = L"窃皮者";
    name_map[L"BP_Clump_C"] = L"肢团";
    name_map[L"BP_Membri_C"] = L"这他吗是啥实体";
    name_map[L"BP_Clump_Poolrooms_C"] = L"池核肢团";
    name_map[L"BP_RoamingPartygoer_Slow_C"] = L"慢速派对客";
}

void visual::main()
{
	if (!gvalue::world || !gvalue::controller)
	{
		return;
	}
	get_all();

    static bool y_down = false;
    if (GetAsyncKeyState('Y') & 0x8000) 
    {
        if (!y_down)
        {
            y_down = true;

            SDK::FVector vec = SDK::UKismetMathLibrary::GetForwardVector(gvalue::controller->GetControlRotation());
            const float forwrad_value = 400.0f;
            SDK::FVector new_loc = gvalue::controller->Pawn->K2_GetActorLocation() + SDK::FVector(vec.X * forwrad_value, vec.Y * forwrad_value, vec.Z * forwrad_value);

            SDK::FHitResult res;
            gvalue::controller->Pawn->K2_SetActorLocation(new_loc, false, &res, true);
        }
    }
    else
    {
        y_down = false;
    }
}

void visual::get_all()
{
	SDK::TArray<SDK::AActor*> actor_list;
	SDK::UGameplayStatics::GetAllActorsOfClass(gvalue::world, SDK::AActor::StaticClass(), &actor_list);
	for (SDK::AActor* actor : actor_list)
	{
		if (!actor || !actor->RootComponent)
		{
			continue;
		}
        
        if (actor->IsA(SDK::ABPCharacter_Demo_C::StaticClass()))
        {
            draw(
                actor->RootComponent,
                SDK::FLinearColor(0.0f, 1.0f, 0.0f, 1.0f),
                L"玩家",
                gvalue::visual_player
            );
            continue;
        }
        if (actor->IsA(SDK::AInteractableActor::StaticClass()))
        {
            SDK::AInteractableActor* target = static_cast<SDK::AInteractableActor*>(actor);
            draw(
                target->StaticMesh,
                SDK::FLinearColor(1.0f, 1.0f, 0.0f, 1.0f),
                SDK::UKismetStringLibrary::Conv_NameToString(target->Class->Name),
                gvalue::visual_item
            );
            continue;
        }
        if (actor->IsA(SDK::ACharacter::StaticClass()))
        {
            draw(
                actor->RootComponent,
                SDK::FLinearColor(1.0f, 0.0f, 0.0f, 1.0f),
                SDK::UKismetStringLibrary::Conv_NameToString(actor->Class->Name),
                gvalue::visual_entity
            );
            continue;
        }
        if (actor->IsA(SDK::ADroppedItem::StaticClass()))
        {
            SDK::ADroppedItem* target = static_cast<SDK::ADroppedItem*>(actor);
            draw(
                target->ItemMesh,
                SDK::FLinearColor(0.0f, 1.0f, 1.0f, 1.0f),
                SDK::UKismetStringLibrary::Conv_NameToString(target->ID),
                gvalue::visual_item
            );
            continue;
        }
	}
}

bool visual::get_box(SDK::USceneComponent* comp, SDK::FVector2D& min, SDK::FVector2D& max)
{
    if (!comp)
    {
        return false;
    }

    SDK::FVector origin, extent;
    float radius;
    SDK::UKismetSystemLibrary::GetComponentBounds(comp, &origin, &extent, &radius);
    const SDK::FVector point[] =
    {
        origin + SDK::FVector(extent.X, extent.Y, extent.Z),
        origin + SDK::FVector(-extent.X, -extent.Y, -extent.Z),

        origin + SDK::FVector(extent.X, -extent.Y, extent.Z),
        origin + SDK::FVector(extent.X, extent.Y, -extent.Z),
        origin + SDK::FVector(extent.X, -extent.Y, -extent.Z),

        origin + SDK::FVector(-extent.X, extent.Y, extent.Z),
        origin + SDK::FVector(-extent.X, extent.Y, -extent.Z),

        origin + SDK::FVector(-extent.X, -extent.Y, extent.Z)
    };

    for (int i = 0; i < 8; i++)
    {
        SDK::FVector2D ori_2d;
        bool in_view = gvalue::controller->ProjectWorldLocationToScreen(point[i], &ori_2d, true);
        if (!in_view)
        {
            return false;
        }

        if (i == 0)
        {
            min.X = ori_2d.X;
            min.Y = ori_2d.Y;
            max.X = ori_2d.X;
            max.Y = ori_2d.Y;
            continue;
        }
        min.X = ori_2d.X < min.X ? ori_2d.X : min.X;
        min.Y = ori_2d.Y < min.Y ? ori_2d.Y : min.Y;
        max.X = ori_2d.X > max.X ? ori_2d.X : max.X;
        max.Y = ori_2d.Y > max.Y ? ori_2d.Y : max.Y;
    }
    return true;
}

void visual::draw(SDK::USceneComponent* comp, const SDK::FLinearColor& color, const UC::FString& name, const s_visual& visual)
{
    SDK::FVector2D min, max;
    bool in_view = get_box(comp, min, max);
    if (in_view)
    {
        if (visual.box)
        {
            render::draw_box(
                min,
                SDK::FVector2D(max.X - min.X, max.Y - min.Y),
                1.0f,
                color
            );
        }
        if (visual.line)
        {
            render::draw_line(
                SDK::FVector2D(gvalue::canvas->SizeX / 2, 0.0f),
                SDK::FVector2D(max.X - (max.X - min.X) / 2, min.Y), 
                1.0f,
                color
            );
        }
        std::wstring draw_str;
        if (visual.name)
        {
            draw_str += find_name(name.CStr()) + L"\n";
        }
        if (visual.distance)
        {
            const float dist = SDK::UKismetMathLibrary::Vector_Distance(
                gvalue::controller->PlayerCameraManager->GetCameraLocation(),
                comp->K2_GetComponentLocation()
            );
            draw_str += std::to_wstring(static_cast<int>(dist / 100.0f)) + L"米\n";
        }
        render::draw_text(
            gvalue::engine->MediumFont,
            draw_str.c_str(),
            SDK::FVector2D(max.X + 5.0f, min.Y),
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

std::wstring visual::find_name(const std::wstring& in_name)
{
    auto it = name_map.find(in_name);
    if (it != name_map.end())
    {
        return it->second;
    }
    wprintf(L"%ls\n", in_name.c_str());
    return in_name;
}
