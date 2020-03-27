// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "ProjectGTF/ProjectGTFGameMode.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeProjectGTFGameMode() {}
// Cross Module References
	PROJECTGTF_API UClass* Z_Construct_UClass_AProjectGTFGameMode_NoRegister();
	PROJECTGTF_API UClass* Z_Construct_UClass_AProjectGTFGameMode();
	ENGINE_API UClass* Z_Construct_UClass_AGameModeBase();
	UPackage* Z_Construct_UPackage__Script_ProjectGTF();
// End Cross Module References
	void AProjectGTFGameMode::StaticRegisterNativesAProjectGTFGameMode()
	{
	}
	UClass* Z_Construct_UClass_AProjectGTFGameMode_NoRegister()
	{
		return AProjectGTFGameMode::StaticClass();
	}
	struct Z_Construct_UClass_AProjectGTFGameMode_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_AProjectGTFGameMode_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AGameModeBase,
		(UObject* (*)())Z_Construct_UPackage__Script_ProjectGTF,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AProjectGTFGameMode_Statics::Class_MetaDataParams[] = {
		{ "HideCategories", "Info Rendering MovementReplication Replication Actor Input Movement Collision Rendering Utilities|Transformation" },
		{ "IncludePath", "ProjectGTFGameMode.h" },
		{ "ModuleRelativePath", "ProjectGTFGameMode.h" },
		{ "ShowCategories", "Input|MouseInput Input|TouchInput" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_AProjectGTFGameMode_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AProjectGTFGameMode>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_AProjectGTFGameMode_Statics::ClassParams = {
		&AProjectGTFGameMode::StaticClass,
		"Game",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		nullptr,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		0,
		0,
		0x008802ACu,
		METADATA_PARAMS(Z_Construct_UClass_AProjectGTFGameMode_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_AProjectGTFGameMode_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_AProjectGTFGameMode()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_AProjectGTFGameMode_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(AProjectGTFGameMode, 3371576506);
	template<> PROJECTGTF_API UClass* StaticClass<AProjectGTFGameMode>()
	{
		return AProjectGTFGameMode::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_AProjectGTFGameMode(Z_Construct_UClass_AProjectGTFGameMode, &AProjectGTFGameMode::StaticClass, TEXT("/Script/ProjectGTF"), TEXT("AProjectGTFGameMode"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(AProjectGTFGameMode);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
