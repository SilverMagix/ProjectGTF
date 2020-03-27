// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "ProjectGTF/EnemyTemplate.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeEnemyTemplate() {}
// Cross Module References
	PROJECTGTF_API UClass* Z_Construct_UClass_AEnemyTemplate_NoRegister();
	PROJECTGTF_API UClass* Z_Construct_UClass_AEnemyTemplate();
	ENGINE_API UClass* Z_Construct_UClass_APawn();
	UPackage* Z_Construct_UPackage__Script_ProjectGTF();
// End Cross Module References
	void AEnemyTemplate::StaticRegisterNativesAEnemyTemplate()
	{
	}
	UClass* Z_Construct_UClass_AEnemyTemplate_NoRegister()
	{
		return AEnemyTemplate::StaticClass();
	}
	struct Z_Construct_UClass_AEnemyTemplate_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_AEnemyTemplate_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_APawn,
		(UObject* (*)())Z_Construct_UPackage__Script_ProjectGTF,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AEnemyTemplate_Statics::Class_MetaDataParams[] = {
		{ "HideCategories", "Navigation" },
		{ "IncludePath", "EnemyTemplate.h" },
		{ "ModuleRelativePath", "EnemyTemplate.h" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_AEnemyTemplate_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AEnemyTemplate>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_AEnemyTemplate_Statics::ClassParams = {
		&AEnemyTemplate::StaticClass,
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
		0x009000A4u,
		METADATA_PARAMS(Z_Construct_UClass_AEnemyTemplate_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_AEnemyTemplate_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_AEnemyTemplate()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_AEnemyTemplate_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(AEnemyTemplate, 2137603697);
	template<> PROJECTGTF_API UClass* StaticClass<AEnemyTemplate>()
	{
		return AEnemyTemplate::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_AEnemyTemplate(Z_Construct_UClass_AEnemyTemplate, &AEnemyTemplate::StaticClass, TEXT("/Script/ProjectGTF"), TEXT("AEnemyTemplate"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(AEnemyTemplate);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
