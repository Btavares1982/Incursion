// © Phoenix-100

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Engine/Classes/GameFramework/SpringArmComponent.h"
#include "Engine/Classes/Camera/CameraComponent.h"
#include "Engine/Classes/Components/SphereComponent.h"
#include "RTSPawn.generated.h"

UCLASS()
class RTS_CAMERA_API ARTSPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ARTSPawn();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RTS Camera")
	class USphereComponent* SphereComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RTS Camera")
	class USpringArmComponent* SpringArm;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RTS Camera")
	class UCameraComponent* CameraComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	FName XAxis = FName("Forward");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	FName YAxis = FName("Sideways");

	// Defines the Area in % of the viewport in which the Movement is activated
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	int MovementZoneInPercent = 25;

	// Ignores the boundaries, allows movement with the mouse off the viewport
	UPROPERTY(EditAnywhere, Category = "Movement")
	bool IgnoreBoundaries = false;

	// By how much the InputAxis should be multiplied
	UPROPERTY(EditAnywhere, Category = "Movement")
	float MovementMultiplier = 50.0f;

	// Smoothness of the Movement
	UPROPERTY(EditAnywhere, Category = "Movement")
	float MovementSmoothness = 4.0f;

	// Whether the RTS Camera should always have the same height or adjust to the world
	UPROPERTY(EditAnywhere, Category = "Height Adjustment")
	bool HeightAdjustment = true;

	// The channel used for the height adjustment
	UPROPERTY(EditAnywhere, Category = "Height Adjustment")
	TEnumAsByte<ECollisionChannel> TraceChannel = ECollisionChannel::ECC_WorldStatic;

	// Whether the camera should be used for the height adjustead
	// instead of the screen center
	UPROPERTY(EditAnywhere, Category = "Height Adjustment", meta=(EditCondition="HeightAdjustment"))
	bool TranceFromCamera = false;

	// The Threshold required to adjust the camera
	UPROPERTY(EditAnywhere, Category = "Height Adjustment", meta=(EditCondition="HeightAdjustment"))
	int Threshold = 1000;

	// Whether the height should be clamped to the start height
	// if it is within the threshold
	UPROPERTY(EditAnywhere, Category = "Height Adjustment", meta=(EditCondition="HeightAdjustment"))
	bool ClampToStartHeight = true;

	UPROPERTY(EditAnywhere, Category = "Height Adjustment", meta=(EditCondition="HeightAdjustment"))
	float HeightAdjustmentSmoothness = 7;

	// By how much the InputAxis should be multiplied
	UPROPERTY(EditAnywhere, Category = "Rotation")
	float RotationMultiplier = 0.5f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rotation")
	FName RotationAxis = FName("Rotate");

	// Smoothness of the Rotation
	UPROPERTY(EditAnywhere, Category = "Rotation")
	float RotationSmoothness = 4.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Zoom")
	FName ZoomAxis = FName("Zoom");

	// By how much the InputAxis should be multiplied
	// Required for high Zoom Speeds
	UPROPERTY(EditAnywhere, Category = "Zoom")
	float ZoomMultiplier = 50.0f;

	// Smoothness of the Zoom
	UPROPERTY(EditAnywhere, Category = "Zoom")
	float ZoomSmoothness = 3.0f;

	// Minimum length of the Spring Arm
	UPROPERTY(EditAnywhere, Category = "Zoom")
	float MinSpringArm = 200.f;

	// Maximum length of the Spring Arm
	UPROPERTY(EditAnywhere, Category = "Zoom")
	float MaxSpringArm = 8000.f;

	// Maximum length of the Spring Arm
	UPROPERTY(EditAnywhere, Category = "Zoom")
	bool UseZoomSteps = false;
	
	// Maximum length of the Spring Arm
	UPROPERTY(EditAnywhere, Category = "Zoom", meta=(EditCondition="UseZoomSteps"))
	int32 ZoomSteps = 10;

	UFUNCTION(BlueprintCallable, Category = "RTS Camera")
	void XMovement(const float AxisValue);

	UFUNCTION(BlueprintCallable, Category = "RTS Camera")
	void YMovement(const float AxisValue);

	UFUNCTION(BlueprintCallable, Category = "RTS Camera")
	void RotateCamera(float AxisValue);

	UFUNCTION(BlueprintCallable, Category = "RTS Camera")
	void Zoom(float AxisValue);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	const int Deactivate = 999999;
	// X ist the minimal value and Y the maximum value
	FVector4 Top;
	FVector4 Bottom;
	FVector4 Left;
	FVector4 Right;

	FVector TargetVector;

	float StartHeight;
	float TargetHeight;
	// To check whether the threshold has been reached
	int PreviousHeight;

	float TargetRotation;
	float TargetZoom;

	void MouseMovement(const float DeltaTime);
	void AdjustHeight(float DeltaTime);

	/**
	 * Positions are the positions to check
	 * The Value X(Positions) needs to be between X-Y(Rules) and Y(Positions) between Z-W(Rules) of the defined rules
	 * @link SetBoundaries @endlink 
	 * The Rules define the bounding Box
	 */
	static bool IsValidMousePosition(const FVector2D Positions, const FVector4 Rules);

	void SetBoundaries();
	void ViewportSizeChanged(FViewport* ViewPort, uint32 val);
	void SetTargetHeight();
	void MoveTo(const float DeltaTime);

	float GetAdjustedDeltaTime() const;
};
