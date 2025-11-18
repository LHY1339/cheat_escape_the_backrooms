#include "visual.h"

#include "_sdk.h"
#include "gvalue.h"
#include "render.h"

#include <unordered_map>
#include <inttypes.h>

std::unordered_map<std::wstring, std::wstring> name_map;

void visual::init()
{
    name_map[L"玩家"] = L"玩家";

    name_map[L"BP_DroppedItem_Juice_C"] = L"果汁";
    name_map[L"BP_DroppedItem_AlmondWater_C"] = L"杏仁水";
    name_map[L"BP_DroppedItem_Flashlight_C"] = L"手电筒";
    name_map[L"BP_DroppedItem_LiquidPain_C"] = L"液态痛苦";
    name_map[L"BP_DroppedItem_EnergyBar_C"] = L"能量棒";
    name_map[L"BP_DroppedItem_DivingHelmet_C"] = L"潜水头盔";
    name_map[L"BP_DroppedItem_FlareGun_C"] = L"信号枪";
    name_map[L"BP_DroppedItem_Rope_C"] = L"绳子";
    name_map[L"BP_DroppedItem_WalkieTalkie_C"] = L"对讲机";
    name_map[L"BP_DroppedItem_Chainsaw_C"] = L"电锯";
    name_map[L"BP_DroppedItem_Ticket_C"] = L"小票";
    name_map[L"BP_DroppedItem_Chainsaw_Fast_C"] = L"快速电锯";
    name_map[L"BP_DroppedItem_Firework_C"] = L"烟花";
    name_map[L"BP_DroppedItem_Glowstick_Yellow_C"] = L"黄色荧光棒";
    name_map[L"BP_DroppedItem_Glowstick_Red_C"] = L"红色荧光棒";
    name_map[L"BP_DroppedItem_Glowstick_Blue_C"] = L"蓝色荧光棒";
    name_map[L"BP_DroppedItem_Glowstick_C"] = L"荧光棒";
    name_map[L"BP_DroppedItem_BugSpray_C"] = L"杀虫喷雾";
    name_map[L"BP_DroppedItem_Camera_C"] = L"相机";
    name_map[L"BP_DroppedItem_Crowbar_C"] = L"撬棍";
    name_map[L"BP_DroppedItem_Thermometer_C"] = L"温度计";
    name_map[L"BP_DroppedItem_LiDAR_C"] = L"扫描仪";
    name_map[L"BP_DroppedItem_Toy_C"] = L"玩具";
    name_map[L"BP_DroppedItem_Knife_C"] = L"刀";
    name_map[L"BP_DroppedItem_Jelly_C"] = L"果冻";

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
    name_map[L"BP_Elevator_188_C"] = L"电梯";
    name_map[L"BP_Door_A_L_C"] = L"门";
    name_map[L"BP_Door_B_R_C"] = L"门";
    name_map[L"BP_Door_B_L_C"] = L"门";
    name_map[L"BP_Door_C_L_C"] = L"门";
    name_map[L"BP_SimpleDoor_C"] = L"门";
    name_map[L"BP_Closet_door_A_L_C"] = L"门";
    name_map[L"BP_Door_sliding_C"] = L"门";
    name_map[L"BP_Latch_C"] = L"门锁";
    name_map[L"BP_CardReader_C"] = L"刷卡机";
    name_map[L"BP_Old_WindTurbine_C"] = L"风力发电机";
    name_map[L"BP_Balloon_Puzzle_C"] = L"拼图气球";
    name_map[L"BP_TV_Puzzle_C"] = L"拼图电视";
    name_map[L"BP_Cassette_C"] = L"电视磁带";
    name_map[L"BP_Photo_Image_C"] = L"电视";
    name_map[L"BP_Lever_C"] = L"拉杆";
    name_map[L"BP_Grassrooms_Exit_Door_C"] = L"门";
    name_map[L"BP_DoubleDoor_922_C"] = L"门";
    name_map[L"BP_CameraButton_C"] = L"摄像头按钮";
    name_map[L"BP_Painting_C"] = L"画";
    name_map[L"BP_HotelLock_C"] = L"门";
    name_map[L"BP_HotelDoors_C"] = L"门";
    name_map[L"BP_Dumbwaiter_C"] = L"小电梯";
    name_map[L"BP_HotelDoor_C"] = L"门";
    name_map[L"BP_Bathroom_Door_C"] = L"门";
    name_map[L"BP_Valve_C"] = L"阀门";
    name_map[L"BP_Balloon_C"] = L"气球";
    name_map[L"BP_Balloon_Float_C"] = L"气球";
    name_map[L"BP_Door_frame_Blueprint_C"] = L"门";
    name_map[L"BP_FunDoor_C"] = L"门";
    name_map[L"BP_CheatParty_C"] = L"作弊派对";
    name_map[L"Tape_BP_C"] = L"磁带";
    name_map[L"BP_TV_C"] = L"电视";
    name_map[L"BP_FireAlarm_C"] = L"火警铃";
    name_map[L"BP_Level94_Door_C"] = L"门";
    name_map[L"BP_LightSwitch_C"] = L"电灯开关";
    name_map[L"BP_Drawer_C"] = L"柜子";
    name_map[L"BP_Level94Rope_C"] = L"绳子";
    name_map[L"BP_RollerCoaster_C"] = L"过山车";
    name_map[L"BP_DarkDoor_C"] = L"门";
    name_map[L"BP_Audience_Chair_C"] = L"椅子";
    name_map[L"BP_Door_974_C"] = L"门";
    name_map[L"BP_DeathSlides_Lever_C"] = L"拉杆";
    name_map[L"BP_Grassrooms_ButtonStand_C"] = L"按钮";
    name_map[L"BP_Grassrooms_Floor_Lever_C"] = L"拉杆";
    name_map[L"BP_Grassrooms_Lever_C"] = L"拉杆";
    name_map[L"BP_RopeZone_C"] = L"绳子";
    name_map[L"BP_Balloon_Key_Fake_C"] = L"假气球";

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
    name_map[L"BP_Wretch_House_C"] = L"悲尸";
    name_map[L"BP_NPC_Type01_C"] = L"大眼怪";
    name_map[L"BP_Faceling_C"] = L"无面灵";
    name_map[L"BP_Hound_C"] = L"猎犬";
    name_map[L"BP_SkinStealer_Hotel_C"] = L"窃皮者";
    name_map[L"BP_Hound_Hotel_C"] = L"猎犬";
    name_map[L"BP_Moth_C"] = L"死亡飞蛾";
    name_map[L"BP_DarkPartyGoer_C"] = L"派对客";
    name_map[L"BP_HidingPartyGoer_C"] = L"派对客";
    name_map[L"Scratcher_BP_C"] = L"这他吗又是啥实体";
    name_map[L"BP_KillerClown_C"] = L"小丑";
    name_map[L"BP_Wretch_C"] = L"悲尸";
    name_map[L"BP_Entity974_C"] = L"Kitty";
    name_map[L"BP_Explorer_C"] = L"探险者尸体";
    name_map[L"BP_Animation_C"] = L"动画";
}

void visual::main()
{
	if (!gvalue::world || !gvalue::controller)
	{
		return;
	}
	get_all();
    camera();
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
        
        if (actor->IsA(SDK::AStaticMeshActor::StaticClass()))
        {
            if (gvalue::draw_mesh && actor->bActorEnableCollision)
            {
                const int dist = static_cast<int>(SDK::UKismetMathLibrary::Vector_Distance(gvalue::controller->PlayerCameraManager->GetCameraLocation(), actor->RootComponent->K2_GetComponentLocation()) / 100.0f);
                if (dist < gvalue::draw_mesh_distance)
                {
                    draw_extent(actor->RootComponent, SDK::FLinearColor(0.5f, 0.5f, 0.5f, 0.5f));
                }
            }
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
                gvalue::visual_interact
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
                SDK::UKismetStringLibrary::Conv_NameToString(target->Class->Name),
                gvalue::visual_item
            );
            continue;
        }
	}
}

void visual::camera()
{
    if (!gvalue::controller->Pawn || !gvalue::controller->Pawn->IsA(SDK::ABPCharacter_Demo_C::StaticClass()))
    {
        return;
    }

    SDK::ABPCharacter_Demo_C* character = static_cast<SDK::ABPCharacter_Demo_C*>(gvalue::controller->Pawn);
    character->CameraComponent->FieldOfView = static_cast<float>(gvalue::fov);
    character->CameraComponent->PostProcessBlendWeight = gvalue::disable_post ? 0.0f : 1.0f;

    static SDK::ACameraActor* tpp_camera = nullptr;
    static SDK::APawn* cur_pawn = nullptr;

    if (cur_pawn != gvalue::controller->Pawn)
    {
        tpp_camera = nullptr;
        cur_pawn = gvalue::controller->Pawn;
    }

    static bool do_once_tpp = false;
    static bool do_once_fpp = false;
    if (gvalue::third_person)
    {
        if (!tpp_camera)
        {
            SDK::FTransform trans;
            SDK::AActor* new_camera = SDK::UGameplayStatics::BeginDeferredActorSpawnFromClass(
                gvalue::world,
                SDK::ACameraActor::StaticClass(),
                trans,
                SDK::ESpawnActorCollisionHandlingMethod::AlwaysSpawn,
                character
            );
            SDK::UGameplayStatics::FinishSpawningActor(new_camera, trans);
            tpp_camera = static_cast<SDK::ACameraActor*>(new_camera);
        }
        else
        {
            SDK::FVector trace_start = character->K2_GetActorLocation();
            trace_start.Z += 60.0f;
            SDK::FVector trace_end = trace_start + SDK::UKismetMathLibrary::GetForwardVector(character->GetControlRotation()) * -1 * gvalue::third_distance;
            SDK::TArray<SDK::AActor*> ignore_actors;
            ignore_actors.Add(character);
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

            tpp_camera->K2_SetActorLocation(result.bBlockingHit ? result.Location : result.TraceEnd, false, nullptr, true);
            tpp_camera->K2_SetActorRotation(character->GetControlRotation(), false);

            tpp_camera->CameraComponent->FieldOfView = static_cast<float>(gvalue::fov);
            tpp_camera->CameraComponent->PostProcessBlendWeight = gvalue::disable_post ? 0.0f : 1.0f;
        }

        if (!do_once_tpp)
        {
            printf("tpp\n");
            gvalue::controller->SetViewTargetWithBlend(
                tpp_camera,
                0.2f,
                SDK::EViewTargetBlendFunction::VTBlend_EaseInOut,
                2.0f,
                false
            );
            do_once_tpp = true;
        }
        do_once_fpp = false;
    }
    else
    {
        if (!do_once_fpp)
        {
            printf("fpp\n");
            gvalue::controller->SetViewTargetWithBlend(
                character,
                0.2f,
                SDK::EViewTargetBlendFunction::VTBlend_EaseInOut,
                2.0f,
                false
            );
            do_once_fpp = true;
        }
        do_once_tpp = false;
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

void visual::draw_extent(SDK::USceneComponent* comp, const SDK::FLinearColor& color)
{
    if (!comp)
    {
        return;
    }

    struct line_01
    {
        SDK::FVector2D p1;
        SDK::FVector2D p2;
    };

    SDK::FVector origin, extent;
    float radius;
    SDK::UKismetSystemLibrary::GetComponentBounds(comp, &origin, &extent, &radius);
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
}

void visual::draw(SDK::USceneComponent* comp, const SDK::FLinearColor& color, const UC::FString& name, const s_visual& visual)
{
    if (!visual.enable)
    {
        return;
    }

    const int dist = static_cast<int>(SDK::UKismetMathLibrary::Vector_Distance(gvalue::controller->PlayerCameraManager->GetCameraLocation(), comp->K2_GetComponentLocation()) / 100.0f);
    if (dist > gvalue::visual_distance)
    {
        return;
    }

    if (visual.extent)
    {
        draw_extent(comp, color);
    }

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
            draw_str += std::to_wstring(dist) + L"米\n";
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
