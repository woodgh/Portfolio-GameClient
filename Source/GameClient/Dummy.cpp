#include "Dummy.h"
#include "DummyUI.h"
#include "AIController.h"
#include "GameFramework/CharacterMovementComponent.h"

ADummy::ADummy()
{
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	springArm_ = CreateDefaultSubobject< USpringArmComponent >(TEXT("SPRINGARM"));
	springArm_->bUsePawnControlRotation = true;
	springArm_->TargetArmLength = 400.0f;
	springArm_->SetRelativeRotation(FRotator(-15.0f, 0.0f, 0.0f));
	springArm_->SetupAttachment(GetCapsuleComponent());
	
	camera_ = CreateDefaultSubobject< UCameraComponent >(TEXT("CAMERA"));
	camera_->bUsePawnControlRotation = false;
	camera_->SetupAttachment(springArm_);

	ui_ = CreateDefaultSubobject< UWidgetComponent >(TEXT("UI"));
	ui_->SetRelativeLocation(FVector(0.0f, 0.0f, 200.0f));
	ui_->SetWidgetSpace(EWidgetSpace::Screen);
	ui_->SetDrawSize(FVector2D(150.0f, 50.0f));
	ui_->SetupAttachment(GetMesh());
	
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Dummy"));

	GetCharacterMovement()->bOrientRotationToMovement = true; 
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); 
	
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetMesh()->SetRelativeLocationAndRotation(
		FVector(0.0f, 0.0f, -90.0f),
		FRotator(0.0f, -90.0f, 0.0f)
	);
	
	static ConstructorHelpers::FObjectFinder< USkeletalMesh > Dummy(
		TEXT("SkeletalMesh'/Game/Dummy/Character/Mesh/SK_Mannequin.SK_Mannequin'")
	);

	if (Dummy.Succeeded())
		GetMesh()->SetSkeletalMesh(Dummy.Object);
		
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);

	static ConstructorHelpers::FClassFinder< UAnimInstance > Animation(
		TEXT("AnimBlueprint'/Game/Dummy/Animations/ThirdPerson_AnimBP.ThirdPerson_AnimBP_C'")
	);

	if (Animation.Succeeded())
		GetMesh()->SetAnimInstanceClass(Animation.Class);

	static ConstructorHelpers::FClassFinder< UUserWidget > UI(
		TEXT("WidgetBlueprint'/Game/UI/Dummy.Dummy_C'")
	);

	if (UI.Succeeded())
		ui_->SetWidgetClass(UI.Class);
}

ADummy::~ADummy()
{
}

void ADummy::MoveToActor(FVector& Location, FVector& Rotation, FVector& Velocity)
{
	AddMovementInput(Velocity);
	SetActorRotation(Rotation.Rotation());
	SetActorLocation(Location);
}

void ADummy::MoveToLocation(FVector& Location, FVector& TargetLocation)
{
	AAIController* AIController = Cast< AAIController >(GetController());

	if (AIController)
		AIController->MoveToLocation(TargetLocation);
}

void ADummy::BeginPlay()
{
	Super::BeginPlay();

	if (ui_)
		Cast< UDummyUI >(ui_->GetUserWidgetObject())->SetOwner(this);
}

void ADummy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ADummy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveFoward"), this, &ADummy::MoveFoward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &ADummy::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ADummy::Turn);
	PlayerInputComponent->BindAxis("LookUp", this, &ADummy::LookUp);
}

void ADummy::MoveFoward(float AxisValue)
{
	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);

	const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

	AddMovementInput(Direction, AxisValue);
}

void ADummy::MoveRight(float AxisValue)
{
	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);

	const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	AddMovementInput(Direction, AxisValue);
}

void ADummy::Turn(float Rate)
{
	AddControllerYawInput(Rate);
}

void ADummy::LookUp(float Rate)
{
	AddControllerPitchInput(Rate);
}
