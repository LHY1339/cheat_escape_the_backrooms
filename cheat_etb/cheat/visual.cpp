#include "visual.h"

#include "gvalue.h"
#include "_sdk.h"
#include "render.h"

#include <unordered_map>
#include <inttypes.h>

class param
{
public:
    inline static std::unordered_map<std::string, std::wstring> name_map;
};

class function
{
public:

};

visual* visual::get()
{
    static visual inst;
    return &inst;
}

void visual::init()
{
    param::name_map["玩家"] = L"玩家";
    param::name_map["BPCharacter_Demo_C"] = L"玩家";

    param::name_map["BP_DroppedItem_Juice_C"] = L"果汁";
    param::name_map["BP_DroppedItem_AlmondWater_C"] = L"杏仁水";
    param::name_map["BP_DroppedItem_Flashlight_C"] = L"手电筒";
    param::name_map["BP_DroppedItem_LiquidPain_C"] = L"液态痛苦";
    param::name_map["BP_DroppedItem_EnergyBar_C"] = L"能量棒";
    param::name_map["BP_DroppedItem_DivingHelmet_C"] = L"潜水头盔";
    param::name_map["BP_DroppedItem_FlareGun_C"] = L"信号枪";
    param::name_map["BP_DroppedItem_Rope_C"] = L"绳子";
    param::name_map["BP_DroppedItem_WalkieTalkie_C"] = L"对讲机";
    param::name_map["BP_DroppedItem_Chainsaw_C"] = L"电锯";
    param::name_map["BP_DroppedItem_Ticket_C"] = L"小票";
    param::name_map["BP_DroppedItem_Chainsaw_Fast_C"] = L"快速电锯";
    param::name_map["BP_DroppedItem_Firework_C"] = L"烟花";
    param::name_map["BP_DroppedItem_Glowstick_Yellow_C"] = L"黄色荧光棒";
    param::name_map["BP_DroppedItem_Glowstick_Red_C"] = L"红色荧光棒";
    param::name_map["BP_DroppedItem_Glowstick_Blue_C"] = L"蓝色荧光棒";
    param::name_map["BP_DroppedItem_Glowstick_C"] = L"荧光棒";
    param::name_map["BP_DroppedItem_BugSpray_C"] = L"杀虫喷雾";
    param::name_map["BP_DroppedItem_Camera_C"] = L"相机";
    param::name_map["BP_DroppedItem_Crowbar_C"] = L"撬棍";
    param::name_map["BP_DroppedItem_Thermometer_C"] = L"温度计";
    param::name_map["BP_DroppedItem_LiDAR_C"] = L"扫描仪";
    param::name_map["BP_DroppedItem_Toy_C"] = L"玩具";
    param::name_map["BP_DroppedItem_Knife_C"] = L"刀";
    param::name_map["BP_DroppedItem_Jelly_C"] = L"果冻";

    param::name_map["BP_Note_C"] = L"笔记";
    param::name_map["BP_MEGDoor_C"] = L"门";
    param::name_map["BP_SchoolDoors_C"] = L"门";
    param::name_map["BP_HubDoor2_C"] = L"门";
    param::name_map["BP_LabDoor_C"] = L"门";
    param::name_map["BP_SmallDoor_C"] = L"门";
    param::name_map["BP_188_Door_C"] = L"门";
    param::name_map["BP_Door_Master_C"] = L"门";
    param::name_map["BP_Elevator_Button_Bunker_C"] = L"电梯按钮";
    param::name_map["BP_Window_C"] = L"窗户";
    param::name_map["BP_DivingGear_C"] = L"潜水装备";
    param::name_map["BP_Ladder_C"] = L"梯子";
    param::name_map["BP_LadderPiece_C"] = L"梯子碎片";
    param::name_map["BP_LadderDoor_C"] = L"门";
    param::name_map["BP_Vent_C"] = L"通风口";
    param::name_map["BP_button_C"] = L"按钮";
    param::name_map["BP_GarageDoor_C"] = L"门";
    param::name_map["BP_Closet_Garage_C"] = L"柜子";
    param::name_map["BP_GarageDoor_C"] = L"门";
    param::name_map["BP_KeyPiece_C"] = L"钥匙";
    param::name_map["BP_KeyTurn_C"] = L"钥匙孔";
    param::name_map["BP_ElevatorButton_C"] = L"电梯按钮";
    param::name_map["BP_DoubleDoor_C"] = L"门";
    param::name_map["BP_Cabinet_C"] = L"柜子";
    param::name_map["BP_BoilerDoor_C"] = L"门";
    param::name_map["BP_IndustrialDoor_2_C"] = L"门";
    param::name_map["BP_metaldoors_C"] = L"门";
    param::name_map["BP_LockedDoor_C"] = L"门";
    param::name_map["BP_OfficeDoor_C"] = L"门";
    param::name_map["BP_ConnectorValve_C"] = L"阀门";
    param::name_map["BP_Elevator_Cave_C"] = L"电梯";
    param::name_map["BP_PlankWall_C"] = L"木板墙";
    param::name_map["BP_ShadowLight_Switch_C"] = L"电灯开关";
    param::name_map["BP_Locker_3_C"] = L"柜子";
    param::name_map["BP_Plank_Door_C"] = L"门";
    param::name_map["BP_Timed_Lever_C"] = L"任务";
    param::name_map["BP_ExitDoor_C"] = L"门";
    param::name_map["BP_EndingsDoor_C"] = L"门";
    param::name_map["BP_Elevator_Button_Hub_C"] = L"电梯按钮";
    param::name_map["BP_Final_Ending_Arcade_C"] = L"结局游戏机";
    param::name_map["BP_Connected_Door_C"] = L"门";
    param::name_map["BP_Gate_Lever_C"] = L"门";
    param::name_map["BP_Blueprint_C"] = L"蓝图";
    param::name_map["BP_Blue_Door_C"] = L"门";
    param::name_map["BP_Dash_Lever_C"] = L"仪表板";
    param::name_map["BP_188_Elevator_Button_C"] = L"电梯按钮";
    param::name_map["BP_Pushable_C"] = L"电视";
    param::name_map["BP_188_Lobby_Doors_C"] = L"门";
    param::name_map["BP_YouCheated_Door_C"] = L"门：你作弊了";
    param::name_map["BP_Pool_Valve_C"] = L"阀门";
    param::name_map["BP_Raft_Passengers_C"] = L"皮划艇";
    param::name_map["BP_Fun_Single_Door_C"] = L"门";
    param::name_map["BP_Fun_Double_Door_C"] = L"门";
    param::name_map["BP_FunKey_C"] = L"钥匙";
    param::name_map["BP_Balloons_Key_C"] = L"钥匙";
    param::name_map["BP_Elevator_188_C"] = L"电梯";
    param::name_map["BP_Door_A_L_C"] = L"门";
    param::name_map["BP_Door_B_R_C"] = L"门";
    param::name_map["BP_Door_B_L_C"] = L"门";
    param::name_map["BP_Door_C_L_C"] = L"门";
    param::name_map["BP_SimpleDoor_C"] = L"门";
    param::name_map["BP_Closet_door_A_L_C"] = L"门";
    param::name_map["BP_Door_sliding_C"] = L"门";
    param::name_map["BP_Latch_C"] = L"门锁";
    param::name_map["BP_CardReader_C"] = L"刷卡机";
    param::name_map["BP_Old_WindTurbine_C"] = L"风力发电机";
    param::name_map["BP_Balloon_Puzzle_C"] = L"拼图气球";
    param::name_map["BP_TV_Puzzle_C"] = L"拼图电视";
    param::name_map["BP_Cassette_C"] = L"电视磁带";
    param::name_map["BP_Photo_Image_C"] = L"电视";
    param::name_map["BP_Lever_C"] = L"拉杆";
    param::name_map["BP_Grassrooms_Exit_Door_C"] = L"门";
    param::name_map["BP_DoubleDoor_922_C"] = L"门";
    param::name_map["BP_CameraButton_C"] = L"摄像头按钮";
    param::name_map["BP_Painting_C"] = L"画";
    param::name_map["BP_HotelLock_C"] = L"门";
    param::name_map["BP_HotelDoors_C"] = L"门";
    param::name_map["BP_Dumbwaiter_C"] = L"小电梯";
    param::name_map["BP_HotelDoor_C"] = L"门";
    param::name_map["BP_Bathroom_Door_C"] = L"门";
    param::name_map["BP_Valve_C"] = L"阀门";
    param::name_map["BP_Balloon_C"] = L"气球";
    param::name_map["BP_Balloon_Float_C"] = L"气球";
    param::name_map["BP_Door_frame_Blueprint_C"] = L"门";
    param::name_map["BP_FunDoor_C"] = L"门";
    param::name_map["BP_CheatParty_C"] = L"作弊派对";
    param::name_map["Tape_BP_C"] = L"磁带";
    param::name_map["BP_TV_C"] = L"电视";
    param::name_map["BP_FireAlarm_C"] = L"火警铃";
    param::name_map["BP_Level94_Door_C"] = L"门";
    param::name_map["BP_LightSwitch_C"] = L"电灯开关";
    param::name_map["BP_Drawer_C"] = L"柜子";
    param::name_map["BP_Level94Rope_C"] = L"绳子";
    param::name_map["BP_RollerCoaster_C"] = L"过山车";
    param::name_map["BP_DarkDoor_C"] = L"门";
    param::name_map["BP_Audience_Chair_C"] = L"椅子";
    param::name_map["BP_Door_974_C"] = L"门";
    param::name_map["BP_DeathSlides_Lever_C"] = L"拉杆";
    param::name_map["BP_Grassrooms_ButtonStand_C"] = L"按钮";
    param::name_map["BP_Grassrooms_Floor_Lever_C"] = L"拉杆";
    param::name_map["BP_Grassrooms_Lever_C"] = L"拉杆";
    param::name_map["BP_RopeZone_C"] = L"绳子";
    param::name_map["BP_Balloon_Key_Fake_C"] = L"假气球";
    param::name_map["BP_MailBox_C"] = L"邮箱";
    param::name_map["BP_Hotel_Note_C"] = L"小条";

    param::name_map["BP_RoamingPartygoer_Idle_C"] = L"派对客";
    param::name_map["BP_RoamingPartygoer_C"] = L"派对客";
    param::name_map["BP_Partypooper_C"] = L"扫兴客";
    param::name_map["Bacteria_BP_C"] = L"细菌";
    param::name_map["BP_SkinStealer_C"] = L"窃皮者";
    param::name_map["Smiler_BP2_C"] = L"笑魇";
    param::name_map["BP_Roaming_Smiler_C"] = L"笑魇";
    param::name_map["BP_Smiler_Dash_C"] = L"笑魇";
    param::name_map["BP_SkinStealer_Cave_C"] = L"窃皮者";
    param::name_map["BP_Cave_Moth_C"] = L"死亡飞蛾";
    param::name_map["Bacteria_Roaming_BP_C"] = L"细菌";
    param::name_map["BP_SkinStealer_Level07_C"] = L"窃皮者";
    param::name_map["BP_Clump_C"] = L"肢团";
    param::name_map["BP_Membri_C"] = L"这他吗是啥实体";
    param::name_map["BP_Clump_Poolrooms_C"] = L"池核肢团";
    param::name_map["BP_RoamingPartygoer_Slow_C"] = L"慢速派对客";
    param::name_map["BP_Wretch_House_C"] = L"悲尸";
    param::name_map["BP_NPC_Type01_C"] = L"大眼怪";
    param::name_map["BP_Faceling_C"] = L"无面灵";
    param::name_map["BP_Hound_C"] = L"猎犬";
    param::name_map["BP_SkinStealer_Hotel_C"] = L"窃皮者";
    param::name_map["BP_Hound_Hotel_C"] = L"猎犬";
    param::name_map["BP_Moth_C"] = L"死亡飞蛾";
    param::name_map["BP_DarkPartyGoer_C"] = L"派对客";
    param::name_map["BP_HidingPartyGoer_C"] = L"派对客";
    param::name_map["Scratcher_BP_C"] = L"这他吗又是啥实体";
    param::name_map["BP_KillerClown_C"] = L"小丑";
    param::name_map["BP_Wretch_C"] = L"悲尸";
    param::name_map["BP_Entity974_C"] = L"Kitty";
    param::name_map["BP_Explorer_C"] = L"探险者尸体";
    param::name_map["BP_Animation_C"] = L"动画";
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
    auto domain = [&](SDK::AActor* actor)
        {
            if (!actor || !actor->RootComponent)
            {
                return;
            }

            //if (actor->IsA(SDK::ABP_Scanner_C::StaticClass()))
            //{
            //    SDK::ABP_Scanner_C* scan = static_cast<SDK::ABP_Scanner_C*>(actor);
            //    
            //    SDK::FVector trace_start = gvalue::controller->PlayerCameraManager->GetCameraLocation();
            //    SDK::FVector trace_end = trace_start + SDK::UKismetMathLibrary::GetForwardVector(gvalue::controller->ControlRotation) * 10000;
            //    SDK::TArray<SDK::AActor*> ignore_actors;
            //    SDK::FHitResult result;
            //    SDK::UKismetSystemLibrary::LineTraceSingle(
            //        gvalue::world,
            //        trace_start,
            //        trace_end,
            //        SDK::ETraceTypeQuery::TraceTypeQuery1,
            //        false,
            //        ignore_actors,
            //        SDK::EDrawDebugTrace::None,
            //        &result,
            //        true,
            //        SDK::FLinearColor(1.0f, 0.0f, 0.0f, 1.0f),
            //        SDK::FLinearColor(0.0f, 1.0f, 0.0f, 1.0f),
            //        0.0f
            //    );

            //    scan->SRV_Lidar(result, SDK::FColor(1, 1, 1, 1));
            //    continue;
            //}

            if (actor->IsA(SDK::AStaticMeshActor::StaticClass()))
            {
                if (gvalue::draw_mesh && actor->bActorEnableCollision)
                {
                    const int dist = static_cast<int>(SDK::UKismetMathLibrary::Vector_Distance(gvalue::controller->PlayerCameraManager->GetCameraLocation(), actor->RootComponent->K2_GetComponentLocation()) / 100.0f);
                    if (dist < gvalue::draw_mesh_distance * 1000)
                    {
                        draw_extent(actor->RootComponent, SDK::FLinearColor(0.5f, 0.5f, 0.5f, 0.5f));
                    }
                }
                return;
            }
            if (actor->IsA(SDK::ABPCharacter_Demo_C::StaticClass()))
            {
                SDK::ABPCharacter_Demo_C* player = static_cast<SDK::ABPCharacter_Demo_C*>(actor);
                const std::wstring name = player->PlayerState ? player->PlayerState->GetPlayerName().ToWString() : L"玩家";
                draw(
                    actor->RootComponent,
                    SDK::FLinearColor(0.0f, 1.0f, 0.0f, 1.0f),
                    "",
                    gvalue::esp_player,
                    false,
                    name
                );
                return;
            }
            if (actor->IsA(SDK::AInteractableActor::StaticClass()))
            {
                SDK::AInteractableActor* target = static_cast<SDK::AInteractableActor*>(actor);
                draw(
                    target->StaticMesh,
                    SDK::FLinearColor(1.0f, 1.0f, 0.0f, 1.0f),
                    target->Class->Name.ToString(),
                    gvalue::esp_interact
                );
                return;
            }
            if (actor->IsA(SDK::ACharacter::StaticClass()))
            {
                draw(
                    actor->RootComponent,
                    SDK::FLinearColor(1.0f, 0.0f, 0.0f, 1.0f),
                    actor->Class->Name.ToString(),
                    gvalue::esp_entity
                );
                return;
            }
            if (actor->IsA(SDK::ADroppedItem::StaticClass()))
            {
                SDK::ADroppedItem* target = static_cast<SDK::ADroppedItem*>(actor);
                draw(
                    target->ItemMesh,
                    SDK::FLinearColor(0.0f, 1.0f, 1.0f, 1.0f),
                    target->Class->Name.ToString(),
                    gvalue::esp_item
                );
                return;
            }
        };

    for (SDK::ULevel* level: gvalue::world->Levels)
    {
        for (SDK::AActor* actor : level->Actors)
        {
            domain(actor);
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
    character->CameraComponent->FieldOfView = static_cast<float>(gvalue::fov * 180);
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
            trace_start += character->GetActorUpVector() * (-250 + gvalue::cam_y * 500);
            trace_start += character->GetActorRightVector() * (-250 + gvalue::cam_x * 500);
            SDK::FVector trace_end = trace_start + SDK::UKismetMathLibrary::GetForwardVector(character->GetControlRotation()) * -1 * gvalue::cam_distance * 1000;
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

            tpp_camera->CameraComponent->FieldOfView = static_cast<float>(gvalue::fov * 180);
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

void visual::draw(SDK::USceneComponent* comp, const SDK::FLinearColor& color, const std::string& name, const s_esp& esp, const bool& use_map, const std::wstring& player_name)
{
    if (!esp.enable)
    {
        return;
    }

    const int dist = static_cast<int>(SDK::UKismetMathLibrary::Vector_Distance(gvalue::controller->PlayerCameraManager->GetCameraLocation(), comp->K2_GetComponentLocation()) / 100.0f);
    if (dist > gvalue::esp_distance * 1000)
    {
        return;
    }

    if (esp.extent)
    {
        draw_extent(comp, color);
    }

    SDK::FVector2D min, max;
    bool in_view = get_box(comp, min, max);
    if (in_view)
    {
        if (esp.box)
        {
            render::draw_box(
                min,
                SDK::FVector2D(max.X - min.X, max.Y - min.Y),
                1.0f,
                color
            );
        }
        if (esp.line)
        {
            render::draw_line(
                SDK::FVector2D(gvalue::canvas->SizeX / 2, 0.0f),
                SDK::FVector2D(max.X - (max.X - min.X) / 2, min.Y),
                1.0f,
                color
            );
        }
        std::wstring draw_str;
        if (esp.name)
        {
            if (use_map)
            {
                draw_str += find_name(name) + L"\n";
            }
            else
            {
                draw_str += L"玩家：" + player_name + L"\n";
            }
        }
        if (esp.distance)
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

std::wstring visual::find_name(const std::string& in_name)
{
    auto it = param::name_map.find(in_name);
    if (it != param::name_map.end())
    {
        return it->second;
    }
    printf("%s\n", in_name.c_str());
    return L"???";
}