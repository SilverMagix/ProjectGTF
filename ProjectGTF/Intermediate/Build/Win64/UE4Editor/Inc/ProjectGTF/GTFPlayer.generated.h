// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
class UAnimMontage;
class UPrimitiveComponent;
class AActor;
struct FVector;
struct FHitResult;
#ifdef PROJECTGTF_GTFPlayer_generated_h
#error "GTFPlayer.generated.h already included, missing '#pragma once' in GTFPlayer.h"
#endif
#define PROJECTGTF_GTFPlayer_generated_h

#define ProjectGTF_Source_ProjectGTF_GTFPlayer_h_15_SPARSE_DATA
#define ProjectGTF_Source_ProjectGTF_GTFPlayer_h_15_RPC_WRAPPERS \
 \
	DECLARE_FUNCTION(execOnRollEnded) \
	{ \
		P_GET_OBJECT(UAnimMontage,Z_Param_Montage); \
		P_GET_UBOOL(Z_Param_binterrupted); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		P_THIS->OnRollEnded(Z_Param_Montage,Z_Param_binterrupted); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execHommingTick) \
	{ \
		P_GET_PROPERTY(UFloatProperty,Z_Param_delta); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		P_THIS->HommingTick(Z_Param_delta); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execOnCompHit) \
	{ \
		P_GET_OBJECT(UPrimitiveComponent,Z_Param_HitComp); \
		P_GET_OBJECT(AActor,Z_Param_OtherActor); \
		P_GET_OBJECT(UPrimitiveComponent,Z_Param_OtherComp); \
		P_GET_STRUCT(FVector,Z_Param_NormalImpulse); \
		P_GET_STRUCT_REF(FHitResult,Z_Param_Out_Hit); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		P_THIS->OnCompHit(Z_Param_HitComp,Z_Param_OtherActor,Z_Param_OtherComp,Z_Param_NormalImpulse,Z_Param_Out_Hit); \
		P_NATIVE_END; \
	}


#define ProjectGTF_Source_ProjectGTF_GTFPlayer_h_15_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execOnRollEnded) \
	{ \
		P_GET_OBJECT(UAnimMontage,Z_Param_Montage); \
		P_GET_UBOOL(Z_Param_binterrupted); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		P_THIS->OnRollEnded(Z_Param_Montage,Z_Param_binterrupted); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execHommingTick) \
	{ \
		P_GET_PROPERTY(UFloatProperty,Z_Param_delta); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		P_THIS->HommingTick(Z_Param_delta); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execOnCompHit) \
	{ \
		P_GET_OBJECT(UPrimitiveComponent,Z_Param_HitComp); \
		P_GET_OBJECT(AActor,Z_Param_OtherActor); \
		P_GET_OBJECT(UPrimitiveComponent,Z_Param_OtherComp); \
		P_GET_STRUCT(FVector,Z_Param_NormalImpulse); \
		P_GET_STRUCT_REF(FHitResult,Z_Param_Out_Hit); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		P_THIS->OnCompHit(Z_Param_HitComp,Z_Param_OtherActor,Z_Param_OtherComp,Z_Param_NormalImpulse,Z_Param_Out_Hit); \
		P_NATIVE_END; \
	}


#define ProjectGTF_Source_ProjectGTF_GTFPlayer_h_15_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesAGTFPlayer(); \
	friend struct Z_Construct_UClass_AGTFPlayer_Statics; \
public: \
	DECLARE_CLASS(AGTFPlayer, ACharacter, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/ProjectGTF"), NO_API) \
	DECLARE_SERIALIZER(AGTFPlayer)


#define ProjectGTF_Source_ProjectGTF_GTFPlayer_h_15_INCLASS \
private: \
	static void StaticRegisterNativesAGTFPlayer(); \
	friend struct Z_Construct_UClass_AGTFPlayer_Statics; \
public: \
	DECLARE_CLASS(AGTFPlayer, ACharacter, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/ProjectGTF"), NO_API) \
	DECLARE_SERIALIZER(AGTFPlayer)


#define ProjectGTF_Source_ProjectGTF_GTFPlayer_h_15_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API AGTFPlayer(const FObjectInitializer& ObjectInitializer); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(AGTFPlayer) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AGTFPlayer); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AGTFPlayer); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API AGTFPlayer(AGTFPlayer&&); \
	NO_API AGTFPlayer(const AGTFPlayer&); \
public:


#define ProjectGTF_Source_ProjectGTF_GTFPlayer_h_15_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API AGTFPlayer(AGTFPlayer&&); \
	NO_API AGTFPlayer(const AGTFPlayer&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AGTFPlayer); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AGTFPlayer); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(AGTFPlayer)


#define ProjectGTF_Source_ProjectGTF_GTFPlayer_h_15_PRIVATE_PROPERTY_OFFSET \
	FORCEINLINE static uint32 __PPO__SideViewCameraComponent() { return STRUCT_OFFSET(AGTFPlayer, SideViewCameraComponent); } \
	FORCEINLINE static uint32 __PPO__CameraBoom() { return STRUCT_OFFSET(AGTFPlayer, CameraBoom); }


#define ProjectGTF_Source_ProjectGTF_GTFPlayer_h_12_PROLOG
#define ProjectGTF_Source_ProjectGTF_GTFPlayer_h_15_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	ProjectGTF_Source_ProjectGTF_GTFPlayer_h_15_PRIVATE_PROPERTY_OFFSET \
	ProjectGTF_Source_ProjectGTF_GTFPlayer_h_15_SPARSE_DATA \
	ProjectGTF_Source_ProjectGTF_GTFPlayer_h_15_RPC_WRAPPERS \
	ProjectGTF_Source_ProjectGTF_GTFPlayer_h_15_INCLASS \
	ProjectGTF_Source_ProjectGTF_GTFPlayer_h_15_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define ProjectGTF_Source_ProjectGTF_GTFPlayer_h_15_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	ProjectGTF_Source_ProjectGTF_GTFPlayer_h_15_PRIVATE_PROPERTY_OFFSET \
	ProjectGTF_Source_ProjectGTF_GTFPlayer_h_15_SPARSE_DATA \
	ProjectGTF_Source_ProjectGTF_GTFPlayer_h_15_RPC_WRAPPERS_NO_PURE_DECLS \
	ProjectGTF_Source_ProjectGTF_GTFPlayer_h_15_INCLASS_NO_PURE_DECLS \
	ProjectGTF_Source_ProjectGTF_GTFPlayer_h_15_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> PROJECTGTF_API UClass* StaticClass<class AGTFPlayer>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID ProjectGTF_Source_ProjectGTF_GTFPlayer_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
