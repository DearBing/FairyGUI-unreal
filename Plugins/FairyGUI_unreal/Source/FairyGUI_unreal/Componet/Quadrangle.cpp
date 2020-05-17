// Fill out your copyright notice in the Description page of Project Settings.


#include "Quadrangle.h"

//UQuadrangle::UQuadrangle()
//{
//	//static ConstructorHelpers::FObjectFinder<UMaterialInterface> MaterialAsset(TEXT("/FairyGUI_unreal/Material/MeshUIBase_Image.MeshUIBase_Image"));
//
//	//if (MaterialAsset.Succeeded())
//	//{
//	//	Materrial = MaterialAsset.Object;
//	//}
//}

void UQuadrangle::OnPopulateMesh(const FGeometry& AllottedGeometry)
{
	VertexData.Empty();
	IndexData.Empty();
	float HalfW = AllottedGeometry.Size.X / 2;
	float HalfH = AllottedGeometry.Size.Y / 2;
	FSlateVertex F1;
	F1.Color = p1.Color;
	F1.Position = FVector2D(-HalfW, HalfH) + p1.Pos;

	FSlateVertex F2;
	F2.Color = p2.Color;
	F2.Position = FVector2D(HalfW, HalfH) + p2.Pos;

	FSlateVertex F3;
	F3.Color = p3.Color;
	F3.Position = FVector2D(HalfW, -HalfH) + p3.Pos;

	FSlateVertex F4;
	F4.Color = p4.Color;
	F4.Position = FVector2D(-HalfW, -HalfH) + p4.Pos;
	VertexData.Add(F1);
	VertexData.Add(F2);
	VertexData.Add(F3);
	VertexData.Add(F4);

	IndexData.Add(0);
	IndexData.Add(1);
	IndexData.Add(2);

	IndexData.Add(2);
	IndexData.Add(3);
	IndexData.Add(0);
}
