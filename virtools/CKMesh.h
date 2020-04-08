#pragma once

#include "CKDef.h"
#include "CKBeObject.h"
#include "CKMaterial.h"

enum ChannelType {
    CHANNELTYPE_MATERIAL = 0,
    CHANNELTYPE_FLOAT1 = 1,
    CHANNELTYPE_FLOAT2 = 2,
    CHANNELTYPE_FLOAT3 = 3,
    CHANNELTYPE_FLOAT4 = 4,

    CHANNELTYPE_COUNT
};

typedef void (*CK_MESHRENDERCALLBACK)(CKRenderContext* Dev, CK3dEntity* Mov, CKMesh* Object, void* Argument);
typedef void (*CK_SUBMESHRENDERCALLBACK)(CKRenderContext* Dev, CK3dEntity* Mov, CKMesh* Object, CKMaterial* mat, void* Argument);

class BML_EXPORT CKMesh : public CKBeObject {
public:
    CKBOOL IsTransparent();
    void SetTransparent(CKBOOL Transparency);
    void SetWrapMode(VXTEXTURE_WRAPMODE Mode);
    VXTEXTURE_WRAPMODE GetWrapMode();
    void SetLitMode(VXMESH_LITMODE Mode);
    VXMESH_LITMODE  GetLitMode();
    CKDWORD GetFlags();
    void SetFlags(CKDWORD Flags);
    BYTE* GetModifierVertices(CKDWORD* Stride);
    int GetModifierVertexCount();
    void ModifierVertexMove(CKBOOL RebuildNormals, CKBOOL RebuildFaceNormals);
    BYTE* GetModifierUVs(CKDWORD* Stride, int channel = -1);
    int GetModifierUVCount(int channel = -1);
    void ModifierUVMove(int Channel = -1);
    int GetVertexCount();
    CKBOOL SetVertexCount(int Count);
    void SetVertexColor(int Index, CKDWORD Color);
    void SetVertexSpecularColor(int Index, CKDWORD Color);
    void SetVertexNormal(int Index, VxVector* Vector);
    void SetVertexPosition(int Index, VxVector* Vector);
    void SetVertexTextureCoordinates(int Index, float u, float v, int channel = -1);
    void* GetColorsPtr(CKDWORD* Stride);
    void* GetSpecularColorsPtr(CKDWORD* Stride);
    void* GetNormalsPtr(CKDWORD* Stride);
    void* GetPositionsPtr(CKDWORD* Stride);
    void* GetTextureCoordinatesPtr(CKDWORD* Stride, int channel = -1);
    CKDWORD GetVertexColor(int Index);
    CKDWORD GetVertexSpecularColor(int Index);
    void GetVertexNormal(int Index, VxVector* Vector);
    void GetVertexPosition(int Index, VxVector* Vector);
    void GetVertexTextureCoordinates(int Index, float* u, float* v, int channel = -1);
    void TranslateVertices(VxVector* Vector);
    void ScaleVertices(VxVector* Vector, VxVector* Pivot = NULL);
    void ScaleVertices(float X, float Y, float Z, VxVector* Pivot = NULL);
    void RotateVertices(VxVector* Vector, float Angle);
    void VertexMove();
    void UVChanged(int Channel = -1);
    void NormalChanged();
    void ColorChanged();
    int GetFaceCount();
    CKBOOL SetFaceCount(int Count);
    WORD* GetFacesIndices();
    void GetFaceVertexIndex(int Index, int& Vertex1, int& Vertex2, int& Vertex3);
    CKMaterial* GetFaceMaterial(int Index);
    const VxVector& GetFaceNormal(int Index);
    CKWORD GetFaceChannelMask(int FaceIndex);
    VxVector& GetFaceVertex(int FaceIndex, int VIndex);
    BYTE* GetFaceNormalsPtr(CKDWORD* Stride);
    void SetFaceVertexIndex(int FaceIndex, int Vertex1, int Vertex2, int Vertex3);
    void SetFaceMaterial(int FaceIndex, CKMaterial* Mat);
    void SetFaceMaterial(int* FaceIndices, int FaceCount, CKMaterial* Mat);
    void ReplaceMaterial(CKMaterial* oldMat, CKMaterial* newMat, CKBOOL Merge = FALSE);
    void ApplyGlobalMaterial(CKMaterial* Mat);
    void DissociateAllFaces();
    CKBOOL SetLineCount(int Count);
    int GetLineCount();
    CKWORD* GetLineIndices();
    void SetLine(int LineIndex, int VIndex1, int VIndex2);
    void GetLine(int LineIndex, int* VIndex1, int* VIndex2);
    void CreateLineStrip(int StartingLine, int Count, int StartingVertexIndex);
    void Clean(CKBOOL KeepVertices = FALSE);
    void InverseWinding();
    void Consolidate();
    void UnOptimize();
    float GetRadius();
    const VxBbox& GetLocalBox();
    void GetBaryCenter(VxVector* Vector);
    int GetChannelCount();
    int AddChannel(CKMaterial* Mat, CKBOOL CopySrcUv = TRUE);
    void RemoveChannel(CKMaterial* Mat);
    void RemoveChannel(int Index);
    int GetChannelByMaterial(CKMaterial* mat);
    void ActivateChannel(int Index, CKBOOL Active = TRUE);
    CKBOOL IsChannelActive(int Index);
    void ActivateAllChannels(CKBOOL Active = TRUE);
    void LitChannel(int Index, CKBOOL Lit = TRUE);
    CKBOOL IsChannelLit(int Index);
    CKDWORD GetChannelFlags(int Index);
    void SetChannelFlags(int Index, CKDWORD Flags);
    CKMaterial* GetChannelMaterial(int Index);
    VXBLEND_MODE GetChannelSourceBlend(int Index);
    VXBLEND_MODE GetChannelDestBlend(int Index);
    void SetChannelMaterial(int Index, CKMaterial* Mat);
    void SetChannelSourceBlend(int Index, VXBLEND_MODE BlendMode);
    void SetChannelDestBlend(int Index, VXBLEND_MODE BlendMode);
    void BuildNormals();
    void BuildFaceNormals();
    CKERROR Render(CKRenderContext* Dev, CK3dEntity* Mov);
    CKBOOL AddPreRenderCallBack(CK_MESHRENDERCALLBACK Function, void* Argument, BOOL Temporary = FALSE);
    CKBOOL RemovePreRenderCallBack(CK_MESHRENDERCALLBACK Function, void* Argument);
    CKBOOL AddPostRenderCallBack(CK_MESHRENDERCALLBACK Function, void* Argument, BOOL Temporary = FALSE);
    CKBOOL RemovePostRenderCallBack(CK_MESHRENDERCALLBACK Function, void* Argument);
    void SetRenderCallBack(CK_MESHRENDERCALLBACK Function, void* Argument);
    void SetDefaultRenderCallBack();
    void RemoveAllCallbacks();
    int GetMaterialCount();
    CKMaterial* GetMaterial(int index);
    int GetVertexWeightsCount();
    void SetVertexWeightsCount(int count);
    float* GetVertexWeightsPtr();
    float GetVertexWeight(int index);
    void SetVertexWeight(int index, float w);
    void LoadVertices(CKStateChunk* chunk);
    void SetVerticesRendered(int count);
    int GetVerticesRendered();
    CKERROR CreatePM();
    void DestroyPM();
    CKBOOL IsPM();
    void EnablePMGeoMorph(CKBOOL enable);
    CKBOOL IsPMGeoMorphEnabled();
    void SetPMGeoMorphStep(int gs);
    int GetPMGeoMorphStep();
    CKBOOL AddSubMeshPreRenderCallBack(CK_SUBMESHRENDERCALLBACK Function, void* Argument, BOOL Temporary = FALSE);
    CKBOOL RemoveSubMeshPreRenderCallBack(CK_SUBMESHRENDERCALLBACK Function, void* Argument);
    CKBOOL AddSubMeshPostRenderCallBack(CK_SUBMESHRENDERCALLBACK Function, void* Argument, BOOL Temporary = FALSE);
    CKBOOL RemoveSubMeshPostRenderCallBack(CK_SUBMESHRENDERCALLBACK Function, void* Argument);
    void SetChannelFaceIndices(int Index, int IndexCount, WORD* Indices);
    int MapPMVertex(int vertex);
    int AddChannelExt(CKMaterial* Mat, CKBOOL CopySrcUv = TRUE, ChannelType ChanType = CHANNELTYPE_MATERIAL);
    ChannelType GetChannelType(int ChanIndex);
    void SetChannelType(int ChanIndex, ChannelType ChanType, BOOL ForceReallocation = FALSE);
    void SetVertexData(int Index, int ChanIndex, void* src);
    void GetVertexData(int Index, int ChanIndex, void* dest);

protected:
    CKMesh();
    ~CKMesh();
};