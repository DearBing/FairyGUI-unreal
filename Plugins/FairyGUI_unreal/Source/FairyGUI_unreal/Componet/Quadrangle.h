// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Base/MeshUIBase.h"
#include "Quadrangle.generated.h"

USTRUCT(BlueprintType)
struct FFairGUIPoint
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (DisplayName = "位置"))
		FVector2D Pos;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (DisplayName = "颜色"))
		FColor Color = FColor::White;
};
/**
 * 
 */
UCLASS()
class FAIRYGUI_UNREAL_API UQuadrangle : public UMeshUIBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ChartConfig", Meta = (DisplayName = "贴图"))
		UTexture2D* Texture;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ChartConfig", Meta = (DisplayName = "p1"))
		FFairGUIPoint p1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ChartConfig", Meta = (DisplayName = "p2"))
		FFairGUIPoint p2;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ChartConfig", Meta = (DisplayName = "p3"))
		FFairGUIPoint p3;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ChartConfig", Meta = (DisplayName = "p4"))
		FFairGUIPoint p4;
//public:
//	UQuadrangle();

protected:
	virtual void OnPopulateMesh(const FGeometry& AllottedGeometry);
	
};
