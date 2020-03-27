// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef PROJECTGTF_ProjectGTFCharacter_generated_h
#error "ProjectGTFCharacter.generated.h already included, missing '#pragma once' in ProjectGTFCharacter.h"
#endif
#define PROJECTGTF_ProjectGTFCharacter_generated_h

#define ProjectGTF_Source_ProjectGTF_ProjectGTFCharacter_h_12_SPARSE_DATA
#define ProjectGTF_Source_ProjectGTF_ProjectGTFCharacter_h_12_RPC_WRAPPERS
#define ProjectGTF_Source_ProjectGTF_ProjectGTFCharacter_h_12_RPC_WRAPPERS_NO_PURE_DECLS
#define ProjectGTF_Source_ProjectGTF_ProjectGTFCharacter_h_12_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesAProjectGTFCharacter(); \
	friend struct Z_Construct_UClass_AProjectGTFCharacter_Statics; \
public: \
	DECLARE_CLASS(AProjectGTFCharacter, ACharacter, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/ProjectGTF"), NO_API) \
	DECLARE_SERIALIZER(AProjectGTFCharacter)


#define ProjectGTF_Source_ProjectGTF_ProjectGTFCharacter_h_12_INCLASS \
private: \
	static void StaticRegisterNativesAProjectGTFCharacter(); \
	friend struct Z_Construct_UClass_AProjectGTFCharacter_Statics; \
public: \
	DECLARE_CLASS(AProjectGTFCharacter, ACharacter, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/ProjectGTF"), NO_API) \
	DECLARE_SERIALIZER(AProjectGTFCharacter)


#define ProjectGTF_Source_ProjectGTF_ProjectGTFCharacter_h_12_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API AProjectGTFCharacter(const FObjectInitializer& ObjectInitializer); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(AProjectGTFCharacter) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AProjectGTFCharacter); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AProjectGTFCharacter); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API AProjectGTFCharacter(AProjectGTFCharacter&&); \
	NO_API AProjectGTFCharacter(const AProjectGTFCharacter&); \
public:


#define ProjectGTF_Source_ProjectGTF_ProjectGTFCharacter_h_12_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API AProjectGTFCharacter(AProjectGTFCharacter&&); \
	NO_API AProjectGTFCharacter(const AProjectGTFCharacter&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AProjectGTFCharacter); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AProjectGTFCharacter); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(AProjectGTFCharacter)


#define ProjectGTF_Source_ProjectGTF_ProjectGTFCharacter_h_12_PRIVATE_PROPERTY_OFFSET \
	FORCEINLINE static uint32 __PPO__SideViewCameraComponent() { return STRUCT_OFFSET(AProjectGTFCharacter, SideViewCameraComponent); } \
	FORCEINLINE static uint32 __PPO__CameraBoom() { return STRUCT_OFFSET(AProjectGTFCharacter, CameraBoom); }


#define ProjectGTF_Source_ProjectGTF_ProjectGTFCharacter_h_9_PROLOG
#define ProjectGTF_Source_ProjectGTF_ProjectGTFCharacter_h_12_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	ProjectGTF_Source_ProjectGTF_ProjectGTFCharacter_h_12_PRIVATE_PROPERTY_OFFSET \
	ProjectGTF_Source_ProjectGTF_ProjectGTFCharacter_h_12_SPARSE_DATA \
	ProjectGTF_Source_ProjectGTF_ProjectGTFCharacter_h_12_RPC_WRAPPERS \
	ProjectGTF_Source_ProjectGTF_ProjectGTFCharacter_h_12_INCLASS \
	ProjectGTF_Source_ProjectGTF_ProjectGTFCharacter_h_12_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define ProjectGTF_Source_ProjectGTF_ProjectGTFCharacter_h_12_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	ProjectGTF_Source_ProjectGTF_ProjectGTFCharacter_h_12_PRIVATE_PROPERTY_OFFSET \
	ProjectGTF_Source_ProjectGTF_ProjectGTFCharacter_h_12_SPARSE_DATA \
	ProjectGTF_Source_ProjectGTF_ProjectGTFCharacter_h_12_RPC_WRAPPERS_NO_PURE_DECLS \
	ProjectGTF_Source_ProjectGTF_ProjectGTFCharacter_h_12_INCLASS_NO_PURE_DECLS \
	ProjectGTF_Source_ProjectGTF_ProjectGTFCharacter_h_12_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> PROJECTGTF_API UClass* StaticClass<class AProjectGTFCharacter>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID ProjectGTF_Source_ProjectGTF_ProjectGTFCharacter_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
