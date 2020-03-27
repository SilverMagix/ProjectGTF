// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "ProjectGTF/GTFPlayer.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeGTFPlayer() {}
// Cross Module References
	PROJECTGTF_API UClass* Z_Construct_UClass_AGTFPlayer_NoRegister();
	PROJECTGTF_API UClass* Z_Construct_UClass_AGTFPlayer();
	ENGINE_API UClass* Z_Construct_UClass_ACharacter();
	UPackage* Z_Construct_UPackage__Script_ProjectGTF();
	PROJECTGTF_API UFunction* Z_Construct_UFunction_AGTFPlayer_HommingTick();
	PROJECTGTF_API UFunction* Z_Construct_UFunction_AGTFPlayer_OnCompHit();
	ENGINE_API UScriptStruct* Z_Construct_UScriptStruct_FHitResult();
	COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FVector();
	ENGINE_API UClass* Z_Construct_UClass_UPrimitiveComponent_NoRegister();
	ENGINE_API UClass* Z_Construct_UClass_AActor_NoRegister();
	PROJECTGTF_API UFunction* Z_Construct_UFunction_AGTFPlayer_OnRollEnded();
	ENGINE_API UClass* Z_Construct_UClass_UAnimMontage_NoRegister();
	ENGINE_API UEnum* Z_Construct_UEnum_Engine_EObjectTypeQuery();
	ENGINE_API UClass* Z_Construct_UClass_USpringArmComponent_NoRegister();
	ENGINE_API UClass* Z_Construct_UClass_UCameraComponent_NoRegister();
// End Cross Module References
	void AGTFPlayer::StaticRegisterNativesAGTFPlayer()
	{
		UClass* Class = AGTFPlayer::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "HommingTick", &AGTFPlayer::execHommingTick },
			{ "OnCompHit", &AGTFPlayer::execOnCompHit },
			{ "OnRollEnded", &AGTFPlayer::execOnRollEnded },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_AGTFPlayer_HommingTick_Statics
	{
		struct GTFPlayer_eventHommingTick_Parms
		{
			float delta;
		};
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_delta;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_AGTFPlayer_HommingTick_Statics::NewProp_delta = { "delta", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(GTFPlayer_eventHommingTick_Parms, delta), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_AGTFPlayer_HommingTick_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AGTFPlayer_HommingTick_Statics::NewProp_delta,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_AGTFPlayer_HommingTick_Statics::Function_MetaDataParams[] = {
		{ "Comment", "// Called to bind functionality to input\n" },
		{ "ModuleRelativePath", "GTFPlayer.h" },
		{ "ToolTip", "Called to bind functionality to input" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_AGTFPlayer_HommingTick_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_AGTFPlayer, nullptr, "HommingTick", nullptr, nullptr, sizeof(GTFPlayer_eventHommingTick_Parms), Z_Construct_UFunction_AGTFPlayer_HommingTick_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_AGTFPlayer_HommingTick_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_AGTFPlayer_HommingTick_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_AGTFPlayer_HommingTick_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_AGTFPlayer_HommingTick()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_AGTFPlayer_HommingTick_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_AGTFPlayer_OnCompHit_Statics
	{
		struct GTFPlayer_eventOnCompHit_Parms
		{
			UPrimitiveComponent* HitComp;
			AActor* OtherActor;
			UPrimitiveComponent* OtherComp;
			FVector NormalImpulse;
			FHitResult Hit;
		};
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Hit_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_Hit;
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_NormalImpulse;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_OtherComp_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_OtherComp;
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_OtherActor;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_HitComp_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_HitComp;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_AGTFPlayer_OnCompHit_Statics::NewProp_Hit_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_AGTFPlayer_OnCompHit_Statics::NewProp_Hit = { "Hit", nullptr, (EPropertyFlags)0x0010008008000182, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(GTFPlayer_eventOnCompHit_Parms, Hit), Z_Construct_UScriptStruct_FHitResult, METADATA_PARAMS(Z_Construct_UFunction_AGTFPlayer_OnCompHit_Statics::NewProp_Hit_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_AGTFPlayer_OnCompHit_Statics::NewProp_Hit_MetaData)) };
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_AGTFPlayer_OnCompHit_Statics::NewProp_NormalImpulse = { "NormalImpulse", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(GTFPlayer_eventOnCompHit_Parms, NormalImpulse), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_AGTFPlayer_OnCompHit_Statics::NewProp_OtherComp_MetaData[] = {
		{ "EditInline", "true" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_AGTFPlayer_OnCompHit_Statics::NewProp_OtherComp = { "OtherComp", nullptr, (EPropertyFlags)0x0010000000080080, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(GTFPlayer_eventOnCompHit_Parms, OtherComp), Z_Construct_UClass_UPrimitiveComponent_NoRegister, METADATA_PARAMS(Z_Construct_UFunction_AGTFPlayer_OnCompHit_Statics::NewProp_OtherComp_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_AGTFPlayer_OnCompHit_Statics::NewProp_OtherComp_MetaData)) };
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_AGTFPlayer_OnCompHit_Statics::NewProp_OtherActor = { "OtherActor", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(GTFPlayer_eventOnCompHit_Parms, OtherActor), Z_Construct_UClass_AActor_NoRegister, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_AGTFPlayer_OnCompHit_Statics::NewProp_HitComp_MetaData[] = {
		{ "EditInline", "true" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_AGTFPlayer_OnCompHit_Statics::NewProp_HitComp = { "HitComp", nullptr, (EPropertyFlags)0x0010000000080080, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(GTFPlayer_eventOnCompHit_Parms, HitComp), Z_Construct_UClass_UPrimitiveComponent_NoRegister, METADATA_PARAMS(Z_Construct_UFunction_AGTFPlayer_OnCompHit_Statics::NewProp_HitComp_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_AGTFPlayer_OnCompHit_Statics::NewProp_HitComp_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_AGTFPlayer_OnCompHit_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AGTFPlayer_OnCompHit_Statics::NewProp_Hit,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AGTFPlayer_OnCompHit_Statics::NewProp_NormalImpulse,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AGTFPlayer_OnCompHit_Statics::NewProp_OtherComp,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AGTFPlayer_OnCompHit_Statics::NewProp_OtherActor,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AGTFPlayer_OnCompHit_Statics::NewProp_HitComp,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_AGTFPlayer_OnCompHit_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "GTFPlayer.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_AGTFPlayer_OnCompHit_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_AGTFPlayer, nullptr, "OnCompHit", nullptr, nullptr, sizeof(GTFPlayer_eventOnCompHit_Parms), Z_Construct_UFunction_AGTFPlayer_OnCompHit_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_AGTFPlayer_OnCompHit_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00C20401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_AGTFPlayer_OnCompHit_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_AGTFPlayer_OnCompHit_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_AGTFPlayer_OnCompHit()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_AGTFPlayer_OnCompHit_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_AGTFPlayer_OnRollEnded_Statics
	{
		struct GTFPlayer_eventOnRollEnded_Parms
		{
			UAnimMontage* Montage;
			bool binterrupted;
		};
		static void NewProp_binterrupted_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_binterrupted;
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_Montage;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	void Z_Construct_UFunction_AGTFPlayer_OnRollEnded_Statics::NewProp_binterrupted_SetBit(void* Obj)
	{
		((GTFPlayer_eventOnRollEnded_Parms*)Obj)->binterrupted = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_AGTFPlayer_OnRollEnded_Statics::NewProp_binterrupted = { "binterrupted", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(GTFPlayer_eventOnRollEnded_Parms), &Z_Construct_UFunction_AGTFPlayer_OnRollEnded_Statics::NewProp_binterrupted_SetBit, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_AGTFPlayer_OnRollEnded_Statics::NewProp_Montage = { "Montage", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(GTFPlayer_eventOnRollEnded_Parms, Montage), Z_Construct_UClass_UAnimMontage_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_AGTFPlayer_OnRollEnded_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AGTFPlayer_OnRollEnded_Statics::NewProp_binterrupted,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AGTFPlayer_OnRollEnded_Statics::NewProp_Montage,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_AGTFPlayer_OnRollEnded_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "GTFPlayer.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_AGTFPlayer_OnRollEnded_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_AGTFPlayer, nullptr, "OnRollEnded", nullptr, nullptr, sizeof(GTFPlayer_eventOnRollEnded_Parms), Z_Construct_UFunction_AGTFPlayer_OnRollEnded_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_AGTFPlayer_OnRollEnded_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_AGTFPlayer_OnRollEnded_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_AGTFPlayer_OnRollEnded_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_AGTFPlayer_OnRollEnded()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_AGTFPlayer_OnRollEnded_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	UClass* Z_Construct_UClass_AGTFPlayer_NoRegister()
	{
		return AGTFPlayer::StaticClass();
	}
	struct Z_Construct_UClass_AGTFPlayer_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_didWallJumpOnce_MetaData[];
#endif
		static void NewProp_didWallJumpOnce_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_didWallJumpOnce;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_isWallStuck_MetaData[];
#endif
		static void NewProp_isWallStuck_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_isWallStuck;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_RollAnim_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_RollAnim;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_TimeToFreeHoming_MetaData[];
#endif
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_TimeToFreeHoming;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_homingImpulsePower_MetaData[];
#endif
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_homingImpulsePower;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_descendWallSpeed_MetaData[];
#endif
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_descendWallSpeed;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_objectsToHomming_MetaData[];
#endif
		static const UE4CodeGen_Private::FArrayPropertyParams NewProp_objectsToHomming;
		static const UE4CodeGen_Private::FBytePropertyParams NewProp_objectsToHomming_Inner;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_HalfSize_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_HalfSize;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_isInAir_MetaData[];
#endif
		static void NewProp_isInAir_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_isInAir;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_isHomming_MetaData[];
#endif
		static void NewProp_isHomming_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_isHomming;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_impulsePower_MetaData[];
#endif
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_impulsePower;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_CameraBoom_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_CameraBoom;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_SideViewCameraComponent_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_SideViewCameraComponent;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_AGTFPlayer_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_ACharacter,
		(UObject* (*)())Z_Construct_UPackage__Script_ProjectGTF,
	};
	const FClassFunctionLinkInfo Z_Construct_UClass_AGTFPlayer_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_AGTFPlayer_HommingTick, "HommingTick" }, // 2349862513
		{ &Z_Construct_UFunction_AGTFPlayer_OnCompHit, "OnCompHit" }, // 876564665
		{ &Z_Construct_UFunction_AGTFPlayer_OnRollEnded, "OnRollEnded" }, // 3211179074
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AGTFPlayer_Statics::Class_MetaDataParams[] = {
		{ "HideCategories", "Navigation" },
		{ "IncludePath", "GTFPlayer.h" },
		{ "ModuleRelativePath", "GTFPlayer.h" },
	};
#endif
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AGTFPlayer_Statics::NewProp_didWallJumpOnce_MetaData[] = {
		{ "Category", "GTFPlayer" },
		{ "ModuleRelativePath", "GTFPlayer.h" },
	};
#endif
	void Z_Construct_UClass_AGTFPlayer_Statics::NewProp_didWallJumpOnce_SetBit(void* Obj)
	{
		((AGTFPlayer*)Obj)->didWallJumpOnce = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UClass_AGTFPlayer_Statics::NewProp_didWallJumpOnce = { "didWallJumpOnce", nullptr, (EPropertyFlags)0x0010000000000004, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(AGTFPlayer), &Z_Construct_UClass_AGTFPlayer_Statics::NewProp_didWallJumpOnce_SetBit, METADATA_PARAMS(Z_Construct_UClass_AGTFPlayer_Statics::NewProp_didWallJumpOnce_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AGTFPlayer_Statics::NewProp_didWallJumpOnce_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AGTFPlayer_Statics::NewProp_isWallStuck_MetaData[] = {
		{ "Category", "GTFPlayer" },
		{ "Comment", "//Wall jump \n" },
		{ "ModuleRelativePath", "GTFPlayer.h" },
		{ "ToolTip", "Wall jump" },
	};
#endif
	void Z_Construct_UClass_AGTFPlayer_Statics::NewProp_isWallStuck_SetBit(void* Obj)
	{
		((AGTFPlayer*)Obj)->isWallStuck = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UClass_AGTFPlayer_Statics::NewProp_isWallStuck = { "isWallStuck", nullptr, (EPropertyFlags)0x0010000000000004, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(AGTFPlayer), &Z_Construct_UClass_AGTFPlayer_Statics::NewProp_isWallStuck_SetBit, METADATA_PARAMS(Z_Construct_UClass_AGTFPlayer_Statics::NewProp_isWallStuck_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AGTFPlayer_Statics::NewProp_isWallStuck_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AGTFPlayer_Statics::NewProp_RollAnim_MetaData[] = {
		{ "Category", "GTFPlayer" },
		{ "Comment", "//Rolling \n" },
		{ "ModuleRelativePath", "GTFPlayer.h" },
		{ "ToolTip", "Rolling" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AGTFPlayer_Statics::NewProp_RollAnim = { "RollAnim", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AGTFPlayer, RollAnim), Z_Construct_UClass_UAnimMontage_NoRegister, METADATA_PARAMS(Z_Construct_UClass_AGTFPlayer_Statics::NewProp_RollAnim_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AGTFPlayer_Statics::NewProp_RollAnim_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AGTFPlayer_Statics::NewProp_TimeToFreeHoming_MetaData[] = {
		{ "Category", "GTFPlayer" },
		{ "ModuleRelativePath", "GTFPlayer.h" },
	};
#endif
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UClass_AGTFPlayer_Statics::NewProp_TimeToFreeHoming = { "TimeToFreeHoming", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AGTFPlayer, TimeToFreeHoming), METADATA_PARAMS(Z_Construct_UClass_AGTFPlayer_Statics::NewProp_TimeToFreeHoming_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AGTFPlayer_Statics::NewProp_TimeToFreeHoming_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AGTFPlayer_Statics::NewProp_homingImpulsePower_MetaData[] = {
		{ "Category", "GTFPlayer" },
		{ "ModuleRelativePath", "GTFPlayer.h" },
	};
#endif
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UClass_AGTFPlayer_Statics::NewProp_homingImpulsePower = { "homingImpulsePower", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AGTFPlayer, homingImpulsePower), METADATA_PARAMS(Z_Construct_UClass_AGTFPlayer_Statics::NewProp_homingImpulsePower_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AGTFPlayer_Statics::NewProp_homingImpulsePower_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AGTFPlayer_Statics::NewProp_descendWallSpeed_MetaData[] = {
		{ "Category", "GTFPlayer" },
		{ "ModuleRelativePath", "GTFPlayer.h" },
	};
#endif
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UClass_AGTFPlayer_Statics::NewProp_descendWallSpeed = { "descendWallSpeed", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AGTFPlayer, descendWallSpeed), METADATA_PARAMS(Z_Construct_UClass_AGTFPlayer_Statics::NewProp_descendWallSpeed_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AGTFPlayer_Statics::NewProp_descendWallSpeed_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AGTFPlayer_Statics::NewProp_objectsToHomming_MetaData[] = {
		{ "Category", "GTFPlayer" },
		{ "ModuleRelativePath", "GTFPlayer.h" },
	};
#endif
	const UE4CodeGen_Private::FArrayPropertyParams Z_Construct_UClass_AGTFPlayer_Statics::NewProp_objectsToHomming = { "objectsToHomming", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AGTFPlayer, objectsToHomming), METADATA_PARAMS(Z_Construct_UClass_AGTFPlayer_Statics::NewProp_objectsToHomming_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AGTFPlayer_Statics::NewProp_objectsToHomming_MetaData)) };
	const UE4CodeGen_Private::FBytePropertyParams Z_Construct_UClass_AGTFPlayer_Statics::NewProp_objectsToHomming_Inner = { "objectsToHomming", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, Z_Construct_UEnum_Engine_EObjectTypeQuery, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AGTFPlayer_Statics::NewProp_HalfSize_MetaData[] = {
		{ "Category", "GTFPlayer" },
		{ "ModuleRelativePath", "GTFPlayer.h" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UClass_AGTFPlayer_Statics::NewProp_HalfSize = { "HalfSize", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AGTFPlayer, HalfSize), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(Z_Construct_UClass_AGTFPlayer_Statics::NewProp_HalfSize_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AGTFPlayer_Statics::NewProp_HalfSize_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AGTFPlayer_Statics::NewProp_isInAir_MetaData[] = {
		{ "Category", "GTFPlayer" },
		{ "ModuleRelativePath", "GTFPlayer.h" },
	};
#endif
	void Z_Construct_UClass_AGTFPlayer_Statics::NewProp_isInAir_SetBit(void* Obj)
	{
		((AGTFPlayer*)Obj)->isInAir = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UClass_AGTFPlayer_Statics::NewProp_isInAir = { "isInAir", nullptr, (EPropertyFlags)0x0010000000000004, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(AGTFPlayer), &Z_Construct_UClass_AGTFPlayer_Statics::NewProp_isInAir_SetBit, METADATA_PARAMS(Z_Construct_UClass_AGTFPlayer_Statics::NewProp_isInAir_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AGTFPlayer_Statics::NewProp_isInAir_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AGTFPlayer_Statics::NewProp_isHomming_MetaData[] = {
		{ "Category", "GTFPlayer" },
		{ "ModuleRelativePath", "GTFPlayer.h" },
	};
#endif
	void Z_Construct_UClass_AGTFPlayer_Statics::NewProp_isHomming_SetBit(void* Obj)
	{
		((AGTFPlayer*)Obj)->isHomming = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UClass_AGTFPlayer_Statics::NewProp_isHomming = { "isHomming", nullptr, (EPropertyFlags)0x0010000000000004, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(AGTFPlayer), &Z_Construct_UClass_AGTFPlayer_Statics::NewProp_isHomming_SetBit, METADATA_PARAMS(Z_Construct_UClass_AGTFPlayer_Statics::NewProp_isHomming_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AGTFPlayer_Statics::NewProp_isHomming_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AGTFPlayer_Statics::NewProp_impulsePower_MetaData[] = {
		{ "Category", "GTFPlayer" },
		{ "Comment", "//Homming Attack values\n" },
		{ "ModuleRelativePath", "GTFPlayer.h" },
		{ "ToolTip", "Homming Attack values" },
	};
#endif
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UClass_AGTFPlayer_Statics::NewProp_impulsePower = { "impulsePower", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AGTFPlayer, impulsePower), METADATA_PARAMS(Z_Construct_UClass_AGTFPlayer_Statics::NewProp_impulsePower_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AGTFPlayer_Statics::NewProp_impulsePower_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AGTFPlayer_Statics::NewProp_CameraBoom_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "Camera" },
		{ "Comment", "/** Camera boom positioning the camera beside the character */" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "GTFPlayer.h" },
		{ "ToolTip", "Camera boom positioning the camera beside the character" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AGTFPlayer_Statics::NewProp_CameraBoom = { "CameraBoom", nullptr, (EPropertyFlags)0x00400000000a001d, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AGTFPlayer, CameraBoom), Z_Construct_UClass_USpringArmComponent_NoRegister, METADATA_PARAMS(Z_Construct_UClass_AGTFPlayer_Statics::NewProp_CameraBoom_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AGTFPlayer_Statics::NewProp_CameraBoom_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AGTFPlayer_Statics::NewProp_SideViewCameraComponent_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "Camera" },
		{ "Comment", "/** Side view camera */" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "GTFPlayer.h" },
		{ "ToolTip", "Side view camera" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AGTFPlayer_Statics::NewProp_SideViewCameraComponent = { "SideViewCameraComponent", nullptr, (EPropertyFlags)0x00400000000a001d, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AGTFPlayer, SideViewCameraComponent), Z_Construct_UClass_UCameraComponent_NoRegister, METADATA_PARAMS(Z_Construct_UClass_AGTFPlayer_Statics::NewProp_SideViewCameraComponent_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AGTFPlayer_Statics::NewProp_SideViewCameraComponent_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_AGTFPlayer_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AGTFPlayer_Statics::NewProp_didWallJumpOnce,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AGTFPlayer_Statics::NewProp_isWallStuck,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AGTFPlayer_Statics::NewProp_RollAnim,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AGTFPlayer_Statics::NewProp_TimeToFreeHoming,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AGTFPlayer_Statics::NewProp_homingImpulsePower,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AGTFPlayer_Statics::NewProp_descendWallSpeed,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AGTFPlayer_Statics::NewProp_objectsToHomming,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AGTFPlayer_Statics::NewProp_objectsToHomming_Inner,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AGTFPlayer_Statics::NewProp_HalfSize,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AGTFPlayer_Statics::NewProp_isInAir,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AGTFPlayer_Statics::NewProp_isHomming,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AGTFPlayer_Statics::NewProp_impulsePower,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AGTFPlayer_Statics::NewProp_CameraBoom,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AGTFPlayer_Statics::NewProp_SideViewCameraComponent,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_AGTFPlayer_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AGTFPlayer>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_AGTFPlayer_Statics::ClassParams = {
		&AGTFPlayer::StaticClass,
		"Game",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		FuncInfo,
		Z_Construct_UClass_AGTFPlayer_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		UE_ARRAY_COUNT(FuncInfo),
		UE_ARRAY_COUNT(Z_Construct_UClass_AGTFPlayer_Statics::PropPointers),
		0,
		0x009000A4u,
		METADATA_PARAMS(Z_Construct_UClass_AGTFPlayer_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_AGTFPlayer_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_AGTFPlayer()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_AGTFPlayer_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(AGTFPlayer, 1900416585);
	template<> PROJECTGTF_API UClass* StaticClass<AGTFPlayer>()
	{
		return AGTFPlayer::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_AGTFPlayer(Z_Construct_UClass_AGTFPlayer, &AGTFPlayer::StaticClass, TEXT("/Script/ProjectGTF"), TEXT("AGTFPlayer"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(AGTFPlayer);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
