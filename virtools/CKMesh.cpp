#include "CKMesh.h"

NAKED CKBOOL CKMesh::IsTransparent() {
    JUMP(0x54);
}

NAKED void CKMesh::SetTransparent(CKBOOL Transparency) {
    JUMP(0x58);
}

NAKED void CKMesh::SetWrapMode(VXTEXTURE_WRAPMODE Mode) {
    JUMP(0x5c);
}

NAKED VXTEXTURE_WRAPMODE CKMesh::GetWrapMode() { JUMP(0x60); }
NAKED void CKMesh::SetLitMode(VXMESH_LITMODE Mode) { JUMP(0x64); }
NAKED VXMESH_LITMODE CKMesh::GetLitMode() { JUMP(0x68); } //
NAKED CKDWORD CKMesh::GetFlags() { JUMP(0x6c); }
NAKED void CKMesh::SetFlags(CKDWORD Flags) { JUMP(0x70); }
NAKED BYTE* CKMesh::GetModifierVertices(CKDWORD* Stride) { JUMP(0x74); }
NAKED int CKMesh::GetModifierVertexCount() { JUMP(0x78); }
NAKED void CKMesh::GetModifierVertex(int iIndex, VxVector* oPosition) { JUMP(0x7c); }
NAKED void CKMesh::SetModifierVertex(int iIndex, VxVector* iPosition) { JUMP(0x80); }
NAKED void CKMesh::ModifierVertexMove(CKBOOL RebuildNormals, CKBOOL RebuildFaceNormals) { JUMP(0x84); }
NAKED BYTE* CKMesh::GetModifierUVs(CKDWORD* Stride, int channel = -1) { JUMP(0x80); } //
NAKED int CKMesh::GetModifierUVCount(int channel = -1) { JUMP(0x84); }
NAKED void CKMesh::ModifierUVMove(int Channel = -1) { JUMP(0x88); }
NAKED int CKMesh::GetVertexCount() { JUMP(0x8c); }
NAKED CKBOOL CKMesh::SetVertexCount(int Count) { JUMP(0x90); }
NAKED void CKMesh::SetVertexColor(int Index, CKDWORD Color) { JUMP(0x94); }
NAKED void CKMesh::SetVertexSpecularColor(int Index, CKDWORD Color) { JUMP(0x98); }
NAKED void CKMesh::SetVertexNormal(int Index, VxVector* Vector) { JUMP(0x9c); }
NAKED void CKMesh::SetVertexPosition(int Index, VxVector* Vector) { JUMP(0xa0); }
NAKED void CKMesh::SetVertexTextureCoordinates(int Index, float u, float v, int channel = -1) { JUMP(0xa4); }
NAKED void* CKMesh::GetColorsPtr(CKDWORD* Stride) { JUMP(0xa8); }
NAKED void* CKMesh::GetSpecularColorsPtr(CKDWORD* Stride) { JUMP(0xac); }
NAKED void* CKMesh::GetNormalsPtr(CKDWORD* Stride) { JUMP(0xb0); }
NAKED void* CKMesh::GetPositionsPtr(CKDWORD* Stride) { JUMP(0xb4); }
NAKED void* CKMesh::GetTextureCoordinatesPtr(CKDWORD* Stride, int channel = -1) { JUMP(0x00); }
NAKED CKDWORD CKMesh::GetVertexColor(int Index) { JUMP(0x00); }
NAKED CKDWORD CKMesh::GetVertexSpecularColor(int Index) { JUMP(0x00); }
NAKED void CKMesh::GetVertexNormal(int Index, VxVector* Vector) { JUMP(0x00); }
NAKED void CKMesh::GetVertexPosition(int Index, VxVector* Vector) { JUMP(0x00); }
NAKED void CKMesh::GetVertexTextureCoordinates(int Index, float* u, float* v, int channel = -1) { JUMP(0x00); }
NAKED void CKMesh::TranslateVertices(VxVector* Vector) { JUMP(0x00); }
NAKED void CKMesh::ScaleVertices(VxVector* Vector, VxVector* Pivot = NULL) { JUMP(0x00); }
NAKED void CKMesh::ScaleVertices(float X, float Y, float Z, VxVector* Pivot = NULL) { JUMP(0x00); }
NAKED void CKMesh::RotateVertices(VxVector* Vector, float Angle) { JUMP(0x00); }
NAKED void CKMesh::VertexMove() { JUMP(0x00); }
NAKED void CKMesh::UVChanged(int Channel = -1) { JUMP(0x00); }
NAKED void CKMesh::NormalChanged() { JUMP(0x00); }
NAKED void CKMesh::ColorChanged() { JUMP(0x00); }
NAKED int CKMesh::GetFaceCount() { JUMP(0x00); }
NAKED CKBOOL CKMesh::SetFaceCount(int Count) { JUMP(0x00); }
NAKED WORD* CKMesh::GetFacesIndices() { JUMP(0x00); }
NAKED void CKMesh::GetFaceVertexIndex(int Index, int& Vertex1, int& Vertex2, int& Vertex3) { JUMP(0x00); }
NAKED CKMaterial* CKMesh::GetFaceMaterial(int Index) { JUMP(0x00); }
NAKED const CKMesh::VxVector& GetFaceNormal(int Index) { JUMP(0x00); }
NAKED CKWORD CKMesh::GetFaceChannelMask(int FaceIndex) { JUMP(0x00); }
NAKED VxVector& CKMesh::GetFaceVertex(int FaceIndex, int VIndex) { JUMP(0x00); }
NAKED BYTE* CKMesh::GetFaceNormalsPtr(CKDWORD* Stride) { JUMP(0x00); }
NAKED void CKMesh::SetFaceVertexIndex(int FaceIndex, int Vertex1, int Vertex2, int Vertex3) { JUMP(0x00); }
NAKED void CKMesh::SetFaceMaterial(int FaceIndex, CKMaterial* Mat) { JUMP(0x00); }
NAKED void CKMesh::SetFaceMaterial(int* FaceIndices, int FaceCount, CKMaterial* Mat) { JUMP(0x00); }
NAKED void CKMesh::ReplaceMaterial(CKMaterial* oldMat, CKMaterial* newMat, CKBOOL Merge = FALSE) { JUMP(0x00); }
NAKED void CKMesh::ApplyGlobalMaterial(CKMaterial* Mat) { JUMP(0x00); }
NAKED void CKMesh::DissociateAllFaces() { JUMP(0x00); }
NAKED CKBOOL CKMesh::SetLineCount(int Count) { JUMP(0x00); }
NAKED int CKMesh::GetLineCount() { JUMP(0x00); }
NAKED CKWORD* CKMesh::GetLineIndices() { JUMP(0x00); }
NAKED void CKMesh::SetLine(int LineIndex, int VIndex1, int VIndex2) { JUMP(0x00); }
NAKED void CKMesh::GetLine(int LineIndex, int* VIndex1, int* VIndex2) { JUMP(0x00); }
NAKED void CKMesh::CreateLineStrip(int StartingLine, int Count, int StartingVertexIndex) { JUMP(0x00); }
NAKED void CKMesh::Clean(CKBOOL KeepVertices = FALSE) { JUMP(0x00); }
NAKED void CKMesh::InverseWinding() { JUMP(0x00); }
NAKED void CKMesh::Consolidate() { JUMP(0x00); }
NAKED void CKMesh::UnOptimize() { JUMP(0x00); }
NAKED float CKMesh::GetRadius() { JUMP(0x00); }
NAKED const CKMesh::VxBbox& GetLocalBox() { JUMP(0x00); }
NAKED void CKMesh::GetBaryCenter(VxVector* Vector) { JUMP(0x00); }
NAKED int CKMesh::GetChannelCount() { JUMP(0x00); }
NAKED int CKMesh::AddChannel(CKMaterial* Mat, CKBOOL CopySrcUv = TRUE) { JUMP(0x00); }
NAKED void CKMesh::RemoveChannel(CKMaterial* Mat) { JUMP(0x00); }
NAKED void CKMesh::RemoveChannel(int Index) { JUMP(0x00); }
NAKED int CKMesh::GetChannelByMaterial(CKMaterial* mat) { JUMP(0x00); }
NAKED void CKMesh::ActivateChannel(int Index, CKBOOL Active = TRUE) { JUMP(0x00); }
NAKED CKBOOL CKMesh::IsChannelActive(int Index) { JUMP(0x00); }
NAKED void CKMesh::ActivateAllChannels(CKBOOL Active = TRUE) { JUMP(0x00); }
NAKED void CKMesh::LitChannel(int Index, CKBOOL Lit = TRUE) { JUMP(0x00); }
NAKED CKBOOL CKMesh::IsChannelLit(int Index) { JUMP(0x00); }
NAKED CKDWORD CKMesh::GetChannelFlags(int Index) { JUMP(0x00); }
NAKED void CKMesh::SetChannelFlags(int Index, CKDWORD Flags) { JUMP(0x00); }
NAKED CKMaterial* CKMesh::GetChannelMaterial(int Index) { JUMP(0x00); }
NAKED VXBLEND_MODE CKMesh::GetChannelSourceBlend(int Index) { JUMP(0x00); }
NAKED VXBLEND_MODE CKMesh::GetChannelDestBlend(int Index) { JUMP(0x00); }
NAKED void CKMesh::SetChannelMaterial(int Index, CKMaterial* Mat) { JUMP(0x00); }
NAKED void CKMesh::SetChannelSourceBlend(int Index, VXBLEND_MODE BlendMode) { JUMP(0x00); }
NAKED void CKMesh::SetChannelDestBlend(int Index, VXBLEND_MODE BlendMode) { JUMP(0x00); }
NAKED void CKMesh::BuildNormals() { JUMP(0x00); }
NAKED void CKMesh::BuildFaceNormals() { JUMP(0x00); }
NAKED CKERROR CKMesh::Render(CKRenderContext* Dev, CK3dEntity* Mov) { JUMP(0x00); }
NAKED CKBOOL CKMesh::AddPreRenderCallBack(CK_MESHRENDERCALLBACK Function, void* Argument, BOOL Temporary = FALSE) { JUMP(0x00); }
NAKED CKBOOL CKMesh::RemovePreRenderCallBack(CK_MESHRENDERCALLBACK Function, void* Argument) { JUMP(0x00); }
NAKED CKBOOL CKMesh::AddPostRenderCallBack(CK_MESHRENDERCALLBACK Function, void* Argument, BOOL Temporary = FALSE) { JUMP(0x00); }
NAKED CKBOOL CKMesh::RemovePostRenderCallBack(CK_MESHRENDERCALLBACK Function, void* Argument) { JUMP(0x00); }
NAKED void CKMesh::SetRenderCallBack(CK_MESHRENDERCALLBACK Function, void* Argument) { JUMP(0x00); }
NAKED void CKMesh::SetDefaultRenderCallBack() { JUMP(0x00); }
NAKED void CKMesh::RemoveAllCallbacks() { JUMP(0x00); }
NAKED const CKMesh::XObjectPointerArray& ComputeMaterialList() { JUMP(0x00); }
NAKED int CKMesh::GetMaterialCount() { JUMP(0x1d8); }
NAKED CKMaterial* CKMesh::GetMaterial(int index) { JUMP(0x1dc); }
NAKED int CKMesh::GetVertexWeightsCount() { JUMP(0x1e0); }
NAKED void CKMesh::SetVertexWeightsCount(int count) { JUMP(0x1e4); }
NAKED float* CKMesh::GetVertexWeightsPtr() { JUMP(0x1e8); }
NAKED float CKMesh::GetVertexWeight(int index) { JUMP(0x1ec); }
NAKED void CKMesh::SetVertexWeight(int index, float w) { JUMP(0x1f0); }
NAKED void CKMesh::LoadVertices(CKStateChunk* chunk) { JUMP(0x1f4); }
NAKED void CKMesh::SetVerticesRendered(int count) { JUMP(0x1f8); }
NAKED int CKMesh::GetVerticesRendered() { JUMP(0x1fc); }
NAKED CKERROR CKMesh::CreatePM() { JUMP(0x200); }
NAKED void CKMesh::DestroyPM() { JUMP(0x204); }
NAKED CKBOOL CKMesh::IsPM() { JUMP(0x208); }
NAKED void CKMesh::EnablePMGeoMorph(CKBOOL enable) { JUMP(0x20c); }
NAKED CKBOOL CKMesh::IsPMGeoMorphEnabled() { JUMP(0x210); }
NAKED void CKMesh::SetPMGeoMorphStep(int gs) { JUMP(0x214); }
NAKED int CKMesh::GetPMGeoMorphStep() { JUMP(0x218); }
NAKED CKBOOL CKMesh::AddSubMeshPreRenderCallBack(CK_SUBMESHRENDERCALLBACK Function, void* Argument, BOOL Temporary = FALSE) { JUMP(0x21c); }
NAKED CKBOOL CKMesh::RemoveSubMeshPreRenderCallBack(CK_SUBMESHRENDERCALLBACK Function, void* Argument) { JUMP(0x220); }
NAKED CKBOOL CKMesh::AddSubMeshPostRenderCallBack(CK_SUBMESHRENDERCALLBACK Function, void* Argument, BOOL Temporary = FALSE) { JUMP(0x224); }
NAKED CKBOOL CKMesh::RemoveSubMeshPostRenderCallBack(CK_SUBMESHRENDERCALLBACK Function, void* Argument) { JUMP(0x228); }
NAKED void CKMesh::SetChannelFaceIndices(int Index, int IndexCount, WORD* Indices) { JUMP(0x22c); }
NAKED int CKMesh::MapPMVertex(int vertex) { JUMP(0x230); }
NAKED int CKMesh::AddChannelExt(CKMaterial* Mat, CKBOOL CopySrcUv = TRUE, ChannelType ChanType = CHANNELTYPE_MATERIAL) { JUMP(0x234); }
NAKED ChannelType CKMesh::GetChannelType(int ChanIndex) { JUMP(0x238); }
NAKED void CKMesh::SetChannelType(int ChanIndex, ChannelType ChanType, BOOL ForceReallocation = FALSE) { JUMP(0x23c); }
NAKED void CKMesh::SetVertexData(int Index, int ChanIndex, void* src) { JUMP(0x240); }
NAKED void CKMesh::GetVertexData(int Index, int ChanIndex, void* dest) { JUMP(0x244); }