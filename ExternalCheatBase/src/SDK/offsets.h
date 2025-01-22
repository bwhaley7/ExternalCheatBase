#pragma once
#include <cstddef>

namespace offsets {
    // Module: client.dll
    namespace client_dll {
        constexpr std::ptrdiff_t dwCSGOInput = 0x1A5E280;
        constexpr std::ptrdiff_t dwEntityList = 0x19F2488;
        constexpr std::ptrdiff_t dwGameEntitySystem = 0x1B0CCF8;
        constexpr std::ptrdiff_t dwGameEntitySystem_highestEntityIndex = 0x1520;
        constexpr std::ptrdiff_t dwGameRules = 0x1A4FE68;
        constexpr std::ptrdiff_t dwGlobalVars = 0x18499C0;
        constexpr std::ptrdiff_t dwGlowManager = 0x1A4F5A8;
        constexpr std::ptrdiff_t dwLocalPlayerController = 0x1A41FD0;
        constexpr std::ptrdiff_t dwLocalPlayerPawn = 0x1855CE8;
        constexpr std::ptrdiff_t dwPlantedC4 = 0x1A59ED0;
        constexpr std::ptrdiff_t dwPrediction = 0x1855B80;
        constexpr std::ptrdiff_t dwSensitivity = 0x1A50B88;
        constexpr std::ptrdiff_t dwSensitivity_sensitivity = 0x40;
        constexpr std::ptrdiff_t dwViewAngles = 0x1A5E650;
        constexpr std::ptrdiff_t dwViewMatrix = 0x1A54550;
        constexpr std::ptrdiff_t dwViewRender = 0x1A54D60;
        constexpr std::ptrdiff_t dwWeaponC4 = 0x19F55F8;

        namespace CCSPlayerController {
            constexpr std::ptrdiff_t m_pInGameMoneyServices = 0x720; // CCSPlayerController_InGameMoneyServices*
            constexpr std::ptrdiff_t m_pInventoryServices = 0x728; // CCSPlayerController_InventoryServices*
            constexpr std::ptrdiff_t m_pActionTrackingServices = 0x730; // CCSPlayerController_ActionTrackingServices*
            constexpr std::ptrdiff_t m_pDamageServices = 0x738; // CCSPlayerController_DamageServices*
            constexpr std::ptrdiff_t m_iPing = 0x740; // uint32
            constexpr std::ptrdiff_t m_bHasCommunicationAbuseMute = 0x744; // bool
            constexpr std::ptrdiff_t m_szCrosshairCodes = 0x748; // CUtlSymbolLarge
            constexpr std::ptrdiff_t m_iPendingTeamNum = 0x750; // uint8
            constexpr std::ptrdiff_t m_flForceTeamTime = 0x754; // GameTime_t
            constexpr std::ptrdiff_t m_iCompTeammateColor = 0x758; // int32
            constexpr std::ptrdiff_t m_bEverPlayedOnTeam = 0x75C; // bool
            constexpr std::ptrdiff_t m_flPreviousForceJoinTeamTime = 0x760; // GameTime_t
            constexpr std::ptrdiff_t m_szClan = 0x768; // CUtlSymbolLarge
            constexpr std::ptrdiff_t m_sSanitizedPlayerName = 0x770; // CUtlString
            constexpr std::ptrdiff_t m_iCoachingTeam = 0x778; // int32
            constexpr std::ptrdiff_t m_nPlayerDominated = 0x780; // uint64
            constexpr std::ptrdiff_t m_nPlayerDominatingMe = 0x788; // uint64
            constexpr std::ptrdiff_t m_iCompetitiveRanking = 0x790; // int32
            constexpr std::ptrdiff_t m_iCompetitiveWins = 0x794; // int32
            constexpr std::ptrdiff_t m_iCompetitiveRankType = 0x798; // int8
            constexpr std::ptrdiff_t m_iCompetitiveRankingPredicted_Win = 0x79C; // int32
            constexpr std::ptrdiff_t m_iCompetitiveRankingPredicted_Loss = 0x7A0; // int32
            constexpr std::ptrdiff_t m_iCompetitiveRankingPredicted_Tie = 0x7A4; // int32
            constexpr std::ptrdiff_t m_nEndMatchNextMapVote = 0x7A8; // int32
            constexpr std::ptrdiff_t m_unActiveQuestId = 0x7AC; // uint16
            constexpr std::ptrdiff_t m_nQuestProgressReason = 0x7B0; // QuestProgress::Reason
            constexpr std::ptrdiff_t m_unPlayerTvControlFlags = 0x7B4; // uint32
            constexpr std::ptrdiff_t m_iDraftIndex = 0x7E0; // int32
            constexpr std::ptrdiff_t m_msQueuedModeDisconnectionTimestamp = 0x7E4; // uint32
            constexpr std::ptrdiff_t m_uiAbandonRecordedReason = 0x7E8; // uint32
            constexpr std::ptrdiff_t m_bCannotBeKicked = 0x7EC; // bool
            constexpr std::ptrdiff_t m_bEverFullyConnected = 0x7ED; // bool
            constexpr std::ptrdiff_t m_bAbandonAllowsSurrender = 0x7EE; // bool
            constexpr std::ptrdiff_t m_bAbandonOffersInstantSurrender = 0x7EF; // bool
            constexpr std::ptrdiff_t m_bDisconnection1MinWarningPrinted = 0x7F0; // bool
            constexpr std::ptrdiff_t m_bScoreReported = 0x7F1; // bool
            constexpr std::ptrdiff_t m_nDisconnectionTick = 0x7F4; // int32
            constexpr std::ptrdiff_t m_bControllingBot = 0x800; // bool
            constexpr std::ptrdiff_t m_bHasControlledBotThisRound = 0x801; // bool
            constexpr std::ptrdiff_t m_bHasBeenControlledByPlayerThisRound = 0x802; // bool
            constexpr std::ptrdiff_t m_nBotsControlledThisRound = 0x804; // int32
            constexpr std::ptrdiff_t m_bCanControlObservedBot = 0x808; // bool
            constexpr std::ptrdiff_t m_hPlayerPawn = 0x80C; // CHandle<C_CSPlayerPawn>
            constexpr std::ptrdiff_t m_hObserverPawn = 0x810; // CHandle<C_CSObserverPawn>
            constexpr std::ptrdiff_t m_bPawnIsAlive = 0x814; // bool
            constexpr std::ptrdiff_t m_iPawnHealth = 0x818; // uint32
            constexpr std::ptrdiff_t m_iPawnArmor = 0x81C; // int32
            constexpr std::ptrdiff_t m_bPawnHasDefuser = 0x820; // bool
            constexpr std::ptrdiff_t m_bPawnHasHelmet = 0x821; // bool
            constexpr std::ptrdiff_t m_nPawnCharacterDefIndex = 0x822; // uint16
            constexpr std::ptrdiff_t m_iPawnLifetimeStart = 0x824; // int32
            constexpr std::ptrdiff_t m_iPawnLifetimeEnd = 0x828; // int32
            constexpr std::ptrdiff_t m_iPawnBotDifficulty = 0x82C; // int32
            constexpr std::ptrdiff_t m_hOriginalControllerOfCurrentPawn = 0x830; // CHandle<CCSPlayerController>
            constexpr std::ptrdiff_t m_iScore = 0x834; // int32
            constexpr std::ptrdiff_t m_recentKillQueue = 0x838; // uint8[8]
            constexpr std::ptrdiff_t m_nFirstKill = 0x840; // uint8
            constexpr std::ptrdiff_t m_nKillCount = 0x841; // uint8
            constexpr std::ptrdiff_t m_bMvpNoMusic = 0x842; // bool
            constexpr std::ptrdiff_t m_eMvpReason = 0x844; // int32
            constexpr std::ptrdiff_t m_iMusicKitID = 0x848; // int32
            constexpr std::ptrdiff_t m_iMusicKitMVPs = 0x84C; // int32
            constexpr std::ptrdiff_t m_iMVPs = 0x850; // int32
            constexpr std::ptrdiff_t m_bIsPlayerNameDirty = 0x854; // bool
            constexpr std::ptrdiff_t m_bFireBulletsSeedSynchronized = 0x855; // bool
        }

        namespace C_BaseEntity {
            constexpr std::ptrdiff_t m_CBodyComponent = 0x38; // CBodyComponent*
            constexpr std::ptrdiff_t m_NetworkTransmitComponent = 0x40; // CNetworkTransmitComponent
            constexpr std::ptrdiff_t m_nLastThinkTick = 0x320; // GameTick_t
            constexpr std::ptrdiff_t m_pGameSceneNode = 0x328; // CGameSceneNode*
            constexpr std::ptrdiff_t m_pRenderComponent = 0x330; // CRenderComponent*
            constexpr std::ptrdiff_t m_pCollision = 0x338; // CCollisionProperty*
            constexpr std::ptrdiff_t m_iMaxHealth = 0x340; // int32
            constexpr std::ptrdiff_t m_iHealth = 0x344; // int32
            constexpr std::ptrdiff_t m_lifeState = 0x348; // uint8
            constexpr std::ptrdiff_t m_bTakesDamage = 0x349; // bool
            constexpr std::ptrdiff_t m_nTakeDamageFlags = 0x350; // TakeDamageFlags_t
            constexpr std::ptrdiff_t m_nPlatformType = 0x358; // EntityPlatformTypes_t
            constexpr std::ptrdiff_t m_ubInterpolationFrame = 0x359; // uint8
            constexpr std::ptrdiff_t m_hSceneObjectController = 0x35C; // CHandle<C_BaseEntity>
            constexpr std::ptrdiff_t m_nNoInterpolationTick = 0x360; // int32
            constexpr std::ptrdiff_t m_nVisibilityNoInterpolationTick = 0x364; // int32
            constexpr std::ptrdiff_t m_flProxyRandomValue = 0x368; // float32
            constexpr std::ptrdiff_t m_iEFlags = 0x36C; // int32
            constexpr std::ptrdiff_t m_nWaterType = 0x370; // uint8
            constexpr std::ptrdiff_t m_bInterpolateEvenWithNoModel = 0x371; // bool
            constexpr std::ptrdiff_t m_bPredictionEligible = 0x372; // bool
            constexpr std::ptrdiff_t m_bApplyLayerMatchIDToModel = 0x373; // bool
            constexpr std::ptrdiff_t m_tokLayerMatchID = 0x374; // CUtlStringToken
            constexpr std::ptrdiff_t m_nSubclassID = 0x378; // CUtlStringToken
            constexpr std::ptrdiff_t m_nSimulationTick = 0x388; // int32
            constexpr std::ptrdiff_t m_iCurrentThinkContext = 0x38C; // int32
            constexpr std::ptrdiff_t m_aThinkFunctions = 0x390; // CUtlVector<thinkfunc_t>
            constexpr std::ptrdiff_t m_bDisabledContextThinks = 0x3A8; // bool
            constexpr std::ptrdiff_t m_flAnimTime = 0x3AC; // float32
            constexpr std::ptrdiff_t m_flSimulationTime = 0x3B0; // float32
            constexpr std::ptrdiff_t m_nSceneObjectOverrideFlags = 0x3B4; // uint8
            constexpr std::ptrdiff_t m_bHasSuccessfullyInterpolated = 0x3B5; // bool
            constexpr std::ptrdiff_t m_bHasAddedVarsToInterpolation = 0x3B6; // bool
            constexpr std::ptrdiff_t m_bRenderEvenWhenNotSuccessfullyInterpolated = 0x3B7; // bool
            constexpr std::ptrdiff_t m_nInterpolationLatchDirtyFlags = 0x3B8; // int32[2]
            constexpr std::ptrdiff_t m_ListEntry = 0x3C0; // uint16[11]
            constexpr std::ptrdiff_t m_flCreateTime = 0x3D8; // GameTime_t
            constexpr std::ptrdiff_t m_flSpeed = 0x3DC; // float32
            constexpr std::ptrdiff_t m_EntClientFlags = 0x3E0; // uint16
            constexpr std::ptrdiff_t m_bClientSideRagdoll = 0x3E2; // bool
            constexpr std::ptrdiff_t m_iTeamNum = 0x3E3; // uint8
            constexpr std::ptrdiff_t m_spawnflags = 0x3E4; // uint32
            constexpr std::ptrdiff_t m_nNextThinkTick = 0x3E8; // GameTick_t
            constexpr std::ptrdiff_t m_fFlags = 0x3EC; // uint32
            constexpr std::ptrdiff_t m_vecAbsVelocity = 0x3F0; // Vector
            constexpr std::ptrdiff_t m_vecVelocity = 0x400; // CNetworkVelocityVector
            constexpr std::ptrdiff_t m_vecBaseVelocity = 0x430; // Vector
            constexpr std::ptrdiff_t m_hEffectEntity = 0x43C; // CHandle<C_BaseEntity>
            constexpr std::ptrdiff_t m_hOwnerEntity = 0x440; // CHandle<C_BaseEntity>
            constexpr std::ptrdiff_t m_MoveCollide = 0x444; // MoveCollide_t
            constexpr std::ptrdiff_t m_MoveType = 0x445; // MoveType_t
            constexpr std::ptrdiff_t m_nActualMoveType = 0x446; // MoveType_t
            constexpr std::ptrdiff_t m_flWaterLevel = 0x448; // float32
            constexpr std::ptrdiff_t m_fEffects = 0x44C; // uint32
            constexpr std::ptrdiff_t m_hGroundEntity = 0x450; // CHandle<C_BaseEntity>
            constexpr std::ptrdiff_t m_nGroundBodyIndex = 0x454; // int32
            constexpr std::ptrdiff_t m_flFriction = 0x458; // float32
            constexpr std::ptrdiff_t m_flElasticity = 0x45C; // float32
            constexpr std::ptrdiff_t m_flGravityScale = 0x460; // float32
            constexpr std::ptrdiff_t m_flTimeScale = 0x464; // float32
            constexpr std::ptrdiff_t m_bAnimatedEveryTick = 0x468; // bool
            constexpr std::ptrdiff_t m_flNavIgnoreUntilTime = 0x46C; // GameTime_t
            constexpr std::ptrdiff_t m_hThink = 0x470; // uint16
            constexpr std::ptrdiff_t m_fBBoxVisFlags = 0x480; // uint8
            constexpr std::ptrdiff_t m_bPredictable = 0x481; // bool
            constexpr std::ptrdiff_t m_bRenderWithViewModels = 0x482; // bool
            constexpr std::ptrdiff_t m_nSplitUserPlayerPredictionSlot = 0x484; // CSplitScreenSlot
            constexpr std::ptrdiff_t m_nFirstPredictableCommand = 0x488; // int32
            constexpr std::ptrdiff_t m_nLastPredictableCommand = 0x48C; // int32
            constexpr std::ptrdiff_t m_hOldMoveParent = 0x490; // CHandle<C_BaseEntity>
            constexpr std::ptrdiff_t m_Particles = 0x498; // CParticleProperty
            constexpr std::ptrdiff_t m_vecPredictedScriptFloats = 0x4C0; // CUtlVector<float32>
            constexpr std::ptrdiff_t m_vecPredictedScriptFloatIDs = 0x4D8; // CUtlVector<int32>
            constexpr std::ptrdiff_t m_nNextScriptVarRecordID = 0x508; // int32
            constexpr std::ptrdiff_t m_vecAngVelocity = 0x518; // QAngle
            constexpr std::ptrdiff_t m_DataChangeEventRef = 0x524; // int32
            constexpr std::ptrdiff_t m_dependencies = 0x528; // CUtlVector<CEntityHandle>
            constexpr std::ptrdiff_t m_nCreationTick = 0x540; // int32
            constexpr std::ptrdiff_t m_bAnimTimeChanged = 0x54D; // bool
            constexpr std::ptrdiff_t m_bSimulationTimeChanged = 0x54E; // bool
            constexpr std::ptrdiff_t m_sUniqueHammerID = 0x558; // CUtlString
            constexpr std::ptrdiff_t m_nBloodType = 0x560; // BloodType
        }

        namespace C_BasePlayerPawn {
            constexpr std::ptrdiff_t m_pWeaponServices = 0x11A8; // CPlayer_WeaponServices*
            constexpr std::ptrdiff_t m_pItemServices = 0x11B0; // CPlayer_ItemServices*
            constexpr std::ptrdiff_t m_pAutoaimServices = 0x11B8; // CPlayer_AutoaimServices*
            constexpr std::ptrdiff_t m_pObserverServices = 0x11C0; // CPlayer_ObserverServices*
            constexpr std::ptrdiff_t m_pWaterServices = 0x11C8; // CPlayer_WaterServices*
            constexpr std::ptrdiff_t m_pUseServices = 0x11D0; // CPlayer_UseServices*
            constexpr std::ptrdiff_t m_pFlashlightServices = 0x11D8; // CPlayer_FlashlightServices*
            constexpr std::ptrdiff_t m_pCameraServices = 0x11E0; // CPlayer_CameraServices*
            constexpr std::ptrdiff_t m_pMovementServices = 0x11E8; // CPlayer_MovementServices*
            constexpr std::ptrdiff_t m_ServerViewAngleChanges = 0x11F8; // 
            constexpr std::ptrdiff_t m_nHighestConsumedServerViewAngleChangeIndex = 0x1248; // uint32
            constexpr std::ptrdiff_t v_angle = 0x124C; // QAngle
            constexpr std::ptrdiff_t v_anglePrevious = 0x1258; // QAngle
            constexpr std::ptrdiff_t m_iHideHUD = 0x1264; // uint32
            constexpr std::ptrdiff_t m_skybox3d = 0x1268; // sky3dparams_t
            constexpr std::ptrdiff_t m_flDeathTime = 0x12F8; // GameTime_t
            constexpr std::ptrdiff_t m_vecPredictionError = 0x12FC; // Vector
            constexpr std::ptrdiff_t m_flPredictionErrorTime = 0x1308; // GameTime_t
            constexpr std::ptrdiff_t m_vecLastCameraSetupLocalOrigin = 0x130C; // Vector
            constexpr std::ptrdiff_t m_flLastCameraSetupTime = 0x1318; // GameTime_t
            constexpr std::ptrdiff_t m_flFOVSensitivityAdjust = 0x131C; // float32
            constexpr std::ptrdiff_t m_flMouseSensitivity = 0x1320; // float32
            constexpr std::ptrdiff_t m_vOldOrigin = 0x1324; // Vector
            constexpr std::ptrdiff_t m_flOldSimulationTime = 0x1330; // float32
            constexpr std::ptrdiff_t m_nLastExecutedCommandNumber = 0x1334; // int32
            constexpr std::ptrdiff_t m_nLastExecutedCommandTick = 0x1338; // int32
            constexpr std::ptrdiff_t m_hController = 0x133C; // CHandle<CBasePlayerController>
            constexpr std::ptrdiff_t m_bIsSwappingToPredictableController = 0x1340; // bool
        }

        namespace CSkeletonInstance {
            constexpr std::ptrdiff_t m_modelState = 0x170; // CModelState
            constexpr std::ptrdiff_t m_bIsAnimationEnabled = 0x3A0; // bool
            constexpr std::ptrdiff_t m_bUseParentRenderBounds = 0x3A1; // bool
            constexpr std::ptrdiff_t m_bDisableSolidCollisionsForHierarchy = 0x3A2; // bool
            constexpr std::ptrdiff_t m_bDirtyMotionType = 0x0; // bitfield:1
            constexpr std::ptrdiff_t m_bIsGeneratingLatchedParentSpaceState = 0x0; // bitfield:1
            constexpr std::ptrdiff_t m_materialGroup = 0x3A4; // CUtlStringToken
            constexpr std::ptrdiff_t m_nHitboxSet = 0x3A8; // uint8
        }

        namespace C_CSPlayerPawnBase {
            constexpr std::ptrdiff_t m_pPingServices = 0x1360; // CCSPlayer_PingServices*
            constexpr std::ptrdiff_t m_pViewModelServices = 0x1368; // CPlayer_ViewModelServices*
            constexpr std::ptrdiff_t m_fRenderingClipPlane = 0x1370; // float32[4]
            constexpr std::ptrdiff_t m_nLastClipPlaneSetupFrame = 0x1380; // int32
            constexpr std::ptrdiff_t m_vecLastClipCameraPos = 0x1384; // Vector
            constexpr std::ptrdiff_t m_vecLastClipCameraForward = 0x1390; // Vector
            constexpr std::ptrdiff_t m_bClipHitStaticWorld = 0x139C; // bool
            constexpr std::ptrdiff_t m_bCachedPlaneIsValid = 0x139D; // bool
            constexpr std::ptrdiff_t m_pClippingWeapon = 0x13A0; // C_CSWeaponBase*
            constexpr std::ptrdiff_t m_previousPlayerState = 0x13A8; // CSPlayerState
            constexpr std::ptrdiff_t m_iPlayerState = 0x13AC; // CSPlayerState
            constexpr std::ptrdiff_t m_bIsRescuing = 0x13B0; // bool
            constexpr std::ptrdiff_t m_fImmuneToGunGameDamageTime = 0x13B4; // GameTime_t
            constexpr std::ptrdiff_t m_fImmuneToGunGameDamageTimeLast = 0x13B8; // GameTime_t
            constexpr std::ptrdiff_t m_bGunGameImmunity = 0x13BC; // bool
            constexpr std::ptrdiff_t m_bHasMovedSinceSpawn = 0x13BD; // bool
            constexpr std::ptrdiff_t m_fMolotovUseTime = 0x13C0; // float32
            constexpr std::ptrdiff_t m_fMolotovDamageTime = 0x13C4; // float32
            constexpr std::ptrdiff_t m_iThrowGrenadeCounter = 0x13C8; // int32
            constexpr std::ptrdiff_t m_flLastSpawnTimeIndex = 0x13CC; // GameTime_t
            constexpr std::ptrdiff_t m_iProgressBarDuration = 0x13D0; // int32
            constexpr std::ptrdiff_t m_flProgressBarStartTime = 0x13D4; // float32
            constexpr std::ptrdiff_t m_vecIntroStartEyePosition = 0x13D8; // Vector
            constexpr std::ptrdiff_t m_vecIntroStartPlayerForward = 0x13E4; // Vector
            constexpr std::ptrdiff_t m_flClientDeathTime = 0x13F0; // GameTime_t
            constexpr std::ptrdiff_t m_bScreenTearFrameCaptured = 0x13F4; // bool
            constexpr std::ptrdiff_t m_flFlashBangTime = 0x13F8; // float32
            constexpr std::ptrdiff_t m_flFlashScreenshotAlpha = 0x13FC; // float32
            constexpr std::ptrdiff_t m_flFlashOverlayAlpha = 0x1400; // float32
            constexpr std::ptrdiff_t m_bFlashBuildUp = 0x1404; // bool
            constexpr std::ptrdiff_t m_bFlashDspHasBeenCleared = 0x1405; // bool
            constexpr std::ptrdiff_t m_bFlashScreenshotHasBeenGrabbed = 0x1406; // bool
            constexpr std::ptrdiff_t m_flFlashMaxAlpha = 0x1408; // float32
            constexpr std::ptrdiff_t m_flFlashDuration = 0x140C; // float32
            constexpr std::ptrdiff_t m_iHealthBarRenderMaskIndex = 0x1410; // int32
            constexpr std::ptrdiff_t m_flHealthFadeValue = 0x1414; // float32
            constexpr std::ptrdiff_t m_flHealthFadeAlpha = 0x1418; // float32
            constexpr std::ptrdiff_t m_flDeathCCWeight = 0x1428; // float32
            constexpr std::ptrdiff_t m_flPrevRoundEndTime = 0x142C; // float32
            constexpr std::ptrdiff_t m_flPrevMatchEndTime = 0x1430; // float32
            constexpr std::ptrdiff_t m_angEyeAngles = 0x1438; // QAngle
            constexpr std::ptrdiff_t m_fNextThinkPushAway = 0x1450; // float32
            constexpr std::ptrdiff_t m_bShouldAutobuyDMWeapons = 0x1454; // bool
            constexpr std::ptrdiff_t m_bShouldAutobuyNow = 0x1455; // bool
            constexpr std::ptrdiff_t m_iIDEntIndex = 0x1458; // CEntityIndex
            constexpr std::ptrdiff_t m_delayTargetIDTimer = 0x1460; // CountdownTimer
            constexpr std::ptrdiff_t m_iTargetItemEntIdx = 0x1478; // CEntityIndex
            constexpr std::ptrdiff_t m_iOldIDEntIndex = 0x147C; // CEntityIndex
            constexpr std::ptrdiff_t m_holdTargetIDTimer = 0x1480; // CountdownTimer
            constexpr std::ptrdiff_t m_flCurrentMusicStartTime = 0x149C; // float32
            constexpr std::ptrdiff_t m_flMusicRoundStartTime = 0x14A0; // float32
            constexpr std::ptrdiff_t m_bDeferStartMusicOnWarmup = 0x14A4; // bool
            constexpr std::ptrdiff_t m_cycleLatch = 0x14A8; // int32
            constexpr std::ptrdiff_t m_serverIntendedCycle = 0x14AC; // float32
            constexpr std::ptrdiff_t m_flLastSmokeOverlayAlpha = 0x14B0; // float32
            constexpr std::ptrdiff_t m_flLastSmokeAge = 0x14B4; // float32
            constexpr std::ptrdiff_t m_vLastSmokeOverlayColor = 0x14B8; // Vector
            constexpr std::ptrdiff_t m_nPlayerSmokedFx = 0x14C4; // ParticleIndex_t
            constexpr std::ptrdiff_t m_nPlayerInfernoBodyFx = 0x14C8; // ParticleIndex_t
            constexpr std::ptrdiff_t m_nPlayerInfernoFootFx = 0x14CC; // ParticleIndex_t
            constexpr std::ptrdiff_t m_flNextMagDropTime = 0x14D0; // float32
            constexpr std::ptrdiff_t m_nLastMagDropAttachmentIndex = 0x14D4; // int32
            constexpr std::ptrdiff_t m_vecLastAliveLocalVelocity = 0x14D8; // Vector
            constexpr std::ptrdiff_t m_bGuardianShouldSprayCustomXMark = 0x1500; // bool
            constexpr std::ptrdiff_t m_hOriginalController = 0x1508; // CHandle<CCSPlayerController>
        }

        namespace C_CSPlayerPawn {
            constexpr std::ptrdiff_t m_pBulletServices = 0x1518; // CCSPlayer_BulletServices*
            constexpr std::ptrdiff_t m_pHostageServices = 0x1520; // CCSPlayer_HostageServices*
            constexpr std::ptrdiff_t m_pBuyServices = 0x1528; // CCSPlayer_BuyServices*
            constexpr std::ptrdiff_t m_pGlowServices = 0x1530; // CCSPlayer_GlowServices*
            constexpr std::ptrdiff_t m_pActionTrackingServices = 0x1538; // CCSPlayer_ActionTrackingServices*
            constexpr std::ptrdiff_t m_pDamageReactServices = 0x1540; // CCSPlayer_DamageReactServices*
            constexpr std::ptrdiff_t m_flHealthShotBoostExpirationTime = 0x1548; // GameTime_t
            constexpr std::ptrdiff_t m_flLastFiredWeaponTime = 0x154C; // GameTime_t
            constexpr std::ptrdiff_t m_bHasFemaleVoice = 0x1550; // bool
            constexpr std::ptrdiff_t m_flLandingTimeSeconds = 0x1554; // float32
            constexpr std::ptrdiff_t m_flOldFallVelocity = 0x1558; // float32
            constexpr std::ptrdiff_t m_szLastPlaceName = 0x155C; // char[18]
            constexpr std::ptrdiff_t m_bPrevDefuser = 0x156E; // bool
            constexpr std::ptrdiff_t m_bPrevHelmet = 0x156F; // bool
            constexpr std::ptrdiff_t m_nPrevArmorVal = 0x1570; // int32
            constexpr std::ptrdiff_t m_nPrevGrenadeAmmoCount = 0x1574; // int32
            constexpr std::ptrdiff_t m_unPreviousWeaponHash = 0x1578; // uint32
            constexpr std::ptrdiff_t m_unWeaponHash = 0x157C; // uint32
            constexpr std::ptrdiff_t m_bInBuyZone = 0x1580; // bool
            constexpr std::ptrdiff_t m_bPreviouslyInBuyZone = 0x1581; // bool
            constexpr std::ptrdiff_t m_aimPunchAngle = 0x1584; // QAngle
            constexpr std::ptrdiff_t m_aimPunchAngleVel = 0x1590; // QAngle
            constexpr std::ptrdiff_t m_aimPunchTickBase = 0x159C; // int32
            constexpr std::ptrdiff_t m_aimPunchTickFraction = 0x15A0; // float32
            constexpr std::ptrdiff_t m_aimPunchCache = 0x15A8; // CUtlVector<QAngle>
            constexpr std::ptrdiff_t m_bInLanding = 0x15C8; // bool
            constexpr std::ptrdiff_t m_flLandingStartTime = 0x15CC; // float32
            constexpr std::ptrdiff_t m_bInHostageRescueZone = 0x15D0; // bool
            constexpr std::ptrdiff_t m_bInBombZone = 0x15D1; // bool
            constexpr std::ptrdiff_t m_bIsBuyMenuOpen = 0x15D2; // bool
            constexpr std::ptrdiff_t m_flTimeOfLastInjury = 0x15D4; // GameTime_t
            constexpr std::ptrdiff_t m_flNextSprayDecalTime = 0x15D8; // GameTime_t
            constexpr std::ptrdiff_t m_iRetakesOffering = 0x1730; // int32
            constexpr std::ptrdiff_t m_iRetakesOfferingCard = 0x1734; // int32
            constexpr std::ptrdiff_t m_bRetakesHasDefuseKit = 0x1738; // bool
            constexpr std::ptrdiff_t m_bRetakesMVPLastRound = 0x1739; // bool
            constexpr std::ptrdiff_t m_iRetakesMVPBoostItem = 0x173C; // int32
            constexpr std::ptrdiff_t m_RetakesMVPBoostExtraUtility = 0x1740; // loadout_slot_t
            constexpr std::ptrdiff_t m_bNeedToReApplyGloves = 0x1760; // bool
            constexpr std::ptrdiff_t m_EconGloves = 0x1768; // C_EconItemView
            constexpr std::ptrdiff_t m_nEconGlovesChanged = 0x1BB0; // uint8
            constexpr std::ptrdiff_t m_bMustSyncRagdollState = 0x1BB1; // bool
            constexpr std::ptrdiff_t m_nRagdollDamageBone = 0x1BB4; // int32
            constexpr std::ptrdiff_t m_vRagdollDamageForce = 0x1BB8; // Vector
            constexpr std::ptrdiff_t m_vRagdollDamagePosition = 0x1BC4; // Vector
            constexpr std::ptrdiff_t m_szRagdollDamageWeaponName = 0x1BD0; // char[64]
            constexpr std::ptrdiff_t m_bRagdollDamageHeadshot = 0x1C10; // bool
            constexpr std::ptrdiff_t m_vRagdollServerOrigin = 0x1C14; // Vector
            constexpr std::ptrdiff_t m_bLastHeadBoneTransformIsValid = 0x2290; // bool
            constexpr std::ptrdiff_t m_lastLandTime = 0x2294; // GameTime_t
            constexpr std::ptrdiff_t m_bOnGroundLastTick = 0x2298; // bool
            constexpr std::ptrdiff_t m_qDeathEyeAngles = 0x22B4; // QAngle
            constexpr std::ptrdiff_t m_bSkipOneHeadConstraintUpdate = 0x22C0; // bool
            constexpr std::ptrdiff_t m_bLeftHanded = 0x22C1; // bool
            constexpr std::ptrdiff_t m_fSwitchedHandednessTime = 0x22C4; // GameTime_t
            constexpr std::ptrdiff_t m_flViewmodelOffsetX = 0x22C8; // float32
            constexpr std::ptrdiff_t m_flViewmodelOffsetY = 0x22CC; // float32
            constexpr std::ptrdiff_t m_flViewmodelOffsetZ = 0x22D0; // float32
            constexpr std::ptrdiff_t m_flViewmodelFOV = 0x22D4; // float32
            constexpr std::ptrdiff_t m_vecPlayerPatchEconIndices = 0x22D8; // uint32[5]
            constexpr std::ptrdiff_t m_GunGameImmunityColor = 0x2310; // Color
            constexpr std::ptrdiff_t m_vecBulletHitModels = 0x2360; // CUtlVector<C_BulletHitModel*>
            constexpr std::ptrdiff_t m_bIsWalking = 0x2378; // bool
            constexpr std::ptrdiff_t m_thirdPersonHeading = 0x2380; // QAngle
            constexpr std::ptrdiff_t m_flSlopeDropOffset = 0x2398; // float32
            constexpr std::ptrdiff_t m_flSlopeDropHeight = 0x23A8; // float32
            constexpr std::ptrdiff_t m_vHeadConstraintOffset = 0x23B8; // Vector
            constexpr std::ptrdiff_t m_entitySpottedState = 0x23D0; // EntitySpottedState_t
            constexpr std::ptrdiff_t m_bIsScoped = 0x23E8; // bool
            constexpr std::ptrdiff_t m_bResumeZoom = 0x23E9; // bool
            constexpr std::ptrdiff_t m_bIsDefusing = 0x23EA; // bool
            constexpr std::ptrdiff_t m_bIsGrabbingHostage = 0x23EB; // bool
            constexpr std::ptrdiff_t m_iBlockingUseActionInProgress = 0x23EC; // CSPlayerBlockingUseAction_t
            constexpr std::ptrdiff_t m_flEmitSoundTime = 0x23F0; // GameTime_t
            constexpr std::ptrdiff_t m_bInNoDefuseArea = 0x23F4; // bool
            constexpr std::ptrdiff_t m_nWhichBombZone = 0x23F8; // int32
            constexpr std::ptrdiff_t m_iShotsFired = 0x23FC; // int32
            constexpr std::ptrdiff_t m_flFlinchStack = 0x2400; // float32
            constexpr std::ptrdiff_t m_flVelocityModifier = 0x2404; // float32
            constexpr std::ptrdiff_t m_flHitHeading = 0x2408; // float32
            constexpr std::ptrdiff_t m_nHitBodyPart = 0x240C; // int32
            constexpr std::ptrdiff_t m_bWaitForNoAttack = 0x2410; // bool
            constexpr std::ptrdiff_t m_ignoreLadderJumpTime = 0x2414; // float32
            constexpr std::ptrdiff_t m_bKilledByHeadshot = 0x2419; // bool
            constexpr std::ptrdiff_t m_ArmorValue = 0x241C; // int32
            constexpr std::ptrdiff_t m_unCurrentEquipmentValue = 0x2420; // uint16
            constexpr std::ptrdiff_t m_unRoundStartEquipmentValue = 0x2422; // uint16
            constexpr std::ptrdiff_t m_unFreezetimeEndEquipmentValue = 0x2424; // uint16
            constexpr std::ptrdiff_t m_nLastKillerIndex = 0x2428; // CEntityIndex
            constexpr std::ptrdiff_t m_bOldIsScoped = 0x242C; // bool
            constexpr std::ptrdiff_t m_bHasDeathInfo = 0x242D; // bool
            constexpr std::ptrdiff_t m_flDeathInfoTime = 0x2430; // float32
            constexpr std::ptrdiff_t m_vecDeathInfoOrigin = 0x2434; // Vector
            constexpr std::ptrdiff_t m_grenadeParameterStashTime = 0x2440; // GameTime_t
            constexpr std::ptrdiff_t m_bGrenadeParametersStashed = 0x2444; // bool
            constexpr std::ptrdiff_t m_angStashedShootAngles = 0x2448; // QAngle
            constexpr std::ptrdiff_t m_vecStashedGrenadeThrowPosition = 0x2454; // Vector
            constexpr std::ptrdiff_t m_vecStashedVelocity = 0x2460; // Vector
            constexpr std::ptrdiff_t m_angShootAngleHistory = 0x246C; // QAngle[2]
            constexpr std::ptrdiff_t m_vecThrowPositionHistory = 0x2484; // Vector[2]
            constexpr std::ptrdiff_t m_vecVelocityHistory = 0x249C; // Vector[2]
            constexpr std::ptrdiff_t m_PredictedDamageTags = 0x24B8; // C_UtlVectorEmbeddedNetworkVar<PredictedDamageTag_t>
            constexpr std::ptrdiff_t m_nPrevHighestReceivedDamageTagTick = 0x2508; // GameTick_t
            constexpr std::ptrdiff_t m_nHighestAppliedDamageTagTick = 0x250C; // int32
        }
        namespace C_CSGameRules {
            constexpr std::ptrdiff_t m_bHasMatchStarted = 0xAC; // bool
            constexpr std::ptrdiff_t m_bFreezePeriod = 0x40; // bool
            constexpr std::ptrdiff_t m_bWarmupPeriod = 0x41; // bool
        }
    }
    // Module: engine2.dll
    namespace engine2_dll {
        constexpr std::ptrdiff_t dwBuildNumber = 0x531BE4;
        constexpr std::ptrdiff_t dwNetworkGameClient = 0x530CE0;
        constexpr std::ptrdiff_t dwNetworkGameClient_clientTickCount = 0x368;
        constexpr std::ptrdiff_t dwNetworkGameClient_deltaTick = 0x27C;
        constexpr std::ptrdiff_t dwNetworkGameClient_isBackgroundMap = 0x281447;
        constexpr std::ptrdiff_t dwNetworkGameClient_localPlayer = 0xF0;
        constexpr std::ptrdiff_t dwNetworkGameClient_maxClients = 0x238;
        constexpr std::ptrdiff_t dwNetworkGameClient_serverTickCount = 0x36C;
        constexpr std::ptrdiff_t dwNetworkGameClient_signOnState = 0x228;
        constexpr std::ptrdiff_t dwWindowHeight = 0x6140D4;
        constexpr std::ptrdiff_t dwWindowWidth = 0x6140D0;
    }
    // Module: inputsystem.dll
    namespace inputsystem_dll {
        constexpr std::ptrdiff_t dwInputSystem = 0x387E0;
    }
    // Module: matchmaking.dll
    namespace matchmaking_dll {
        constexpr std::ptrdiff_t dwGameTypes = 0x1A41B0;
        constexpr std::ptrdiff_t dwGameTypes_mapName = 0x120;
    }
    // Module: soundsystem.dll
    namespace soundsystem_dll {
        constexpr std::ptrdiff_t dwSoundSystem = 0x39A5E0;
        constexpr std::ptrdiff_t dwSoundSystem_engineViewData = 0x7C;
    }
}