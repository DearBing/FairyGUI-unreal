// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Widget.h"
#include "MeshUIBase.generated.h"

/**
 * 
 */
UCLASS()
class FAIRYGUI_UNREAL_API UMeshUIBase : public UWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ChartConfig", Meta = (DisplayName = "材质球"))
		UMaterialInterface* Materrial;

public:
	UMeshUIBase();

	//~ Begin UWidget Interface
	virtual void SynchronizeProperties() override;
	//~ End UWidget Interface

protected:
	//~ Begin UWidget Interface
	virtual TSharedRef<SWidget> RebuildWidget() override;
	//~ End UWidget Interface
	virtual void OnPopulateMesh(const FGeometry& AllottedGeometry);
	void PushUpdateVertext(const FVector2D& Position, float Scale);

	TArray<FSlateVertex> VertexData;
	TArray<SlateIndex> IndexData;

	float FirstX;//第一个X值
	float FirstY;//第一个Y值
	float Width;//宽度值
	float Height;//高度值
private:

	TSharedPtr<class SUIMeshWidget> MyMesh;
	friend class SUIMeshWidget;

#if WITH_EDITOR
public:
	// UWidget interface
	virtual const FText GetPaletteCategory() override;
	// End UWidget interface
#endif
};
