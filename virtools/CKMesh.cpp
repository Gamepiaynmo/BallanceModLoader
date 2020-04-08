#include "CKMesh.h"

NAKED CKBOOL CKMesh::IsTransparent() {
    JUMPV(0x54);
}

NAKED void CKMesh::SetTransparent(CKBOOL Transparency) {
    JUMPV(0x58);
}

NAKED void CKMesh::SetWrapMode(VXTEXTURE_WRAPMODE Mode) {
    JUMPV(0x5c);
}

NAKED VXTEXTURE_WRAPMODE CKMesh::GetWrapMode() {
    JUMPV(0x60);
}

NAKED void CKMesh::SetLitMode(VXMESH_LITMODE Mode) {
    JUMPV(0x64);
}

NAKED VXMESH_LITMODE CKMesh::GetLitMode() {
    JUMPV(0x68);
}

NAKED CKDWORD CKMesh::GetFlags() {
    JUMPV(0x6c);
}

NAKED void CKMesh::SetFlags(CKDWORD Flags) {
	JUMPV(0x70);
}

NAKED BYTE* CKMesh::GetModifierVertices(CKDWORD* Stride) {
	JUMPV(0x74);
}

NAKED int CKMesh::GetModifierVertexCount() {
	JUMPV(0x78);
}

NAKED void CKMesh::ModifierVertexMove(CKBOOL RebuildNormals, CKBOOL RebuildFaceNormals) {
	JUMPV(0x7c);
}

NAKED BYTE* CKMesh::GetModifierUVs(CKDWORD* Stride, int channel) {
	JUMPV(0x80);
}

NAKED int CKMesh::GetModifierUVCount(int channel) {
	JUMPV(0x84);
}

NAKED void CKMesh::ModifierUVMove(int Channel) {
	JUMPV(0x88);
}

NAKED int CKMesh::GetVertexCount() {
	JUMPV(0x8c);
}

NAKED CKBOOL CKMesh::SetVertexCount(int Count) {
	JUMPV(0x90);
}

NAKED void CKMesh::SetVertexColor(int Index, CKDWORD Color) {
	JUMPV(0x94);
}

NAKED void CKMesh::SetVertexSpecularColor(int Index, CKDWORD Color) {
	JUMPV(0x98);
}

NAKED void CKMesh::SetVertexNormal(int Index, VxVector* Vector) {
	JUMPV(0x9c);
}

NAKED void CKMesh::SetVertexPosition(int Index, VxVector* Vector) {
	JUMPV(0xa0);
}

NAKED void CKMesh::SetVertexTextureCoordinates(int Index, float u, float v, int channel) {
	JUMPV(0xa4);
}

NAKED void* CKMesh::GetColorsPtr(CKDWORD* Stride) {
	JUMPV(0xa8);
}

NAKED void* CKMesh::GetSpecularColorsPtr(CKDWORD* Stride) {
	JUMPV(0xac);
}

NAKED void* CKMesh::GetNormalsPtr(CKDWORD* Stride) {
	JUMPV(0xb0);
}

NAKED void* CKMesh::GetPositionsPtr(CKDWORD* Stride) {
	JUMPV(0xb4);
}

NAKED void* CKMesh::GetTextureCoordinatesPtr(CKDWORD* Stride, int channel) {
	JUMPV(0xb8);
}

NAKED CKDWORD CKMesh::GetVertexColor(int Index) {
	JUMPV(0xbc);
}

NAKED CKDWORD CKMesh::GetVertexSpecularColor(int Index) {
	JUMPV(0xc0);
}

NAKED void CKMesh::GetVertexNormal(int Index, VxVector* Vector) {
	JUMPV(0xc4);
}

NAKED void CKMesh::GetVertexPosition(int Index, VxVector* Vector) {
	JUMPV(0xc8);
}

NAKED void CKMesh::GetVertexTextureCoordinates(int Index, float* u, float* v, int channel) {
	JUMPV(0xcc);
}

NAKED void CKMesh::TranslateVertices(VxVector* Vector) {
	JUMPV(0xd0);
}

NAKED void CKMesh::ScaleVertices(VxVector* Vector, VxVector* Pivot) {
	JUMPV(0xd4);
}

NAKED void CKMesh::ScaleVertices(float X, float Y, float Z, VxVector* Pivot) {
	JUMPV(0xd8);
}

NAKED void CKMesh::RotateVertices(VxVector* Vector, float Angle) {
	JUMPV(0xdc);
}

NAKED void CKMesh::VertexMove() {
	JUMPV(0xe0);
}

NAKED void CKMesh::UVChanged(int Channel) {
	JUMPV(0xe4);
}

NAKED void CKMesh::NormalChanged() {
	JUMPV(0xe8);
}

NAKED void CKMesh::ColorChanged() {
	JUMPV(0xec);
}

NAKED int CKMesh::GetFaceCount() {
	JUMPV(0xf0);
}

NAKED CKBOOL CKMesh::SetFaceCount(int Count) {
	JUMPV(0xf4);
}

NAKED WORD* CKMesh::GetFacesIndices() {
	JUMPV(0xf8);
}

NAKED void CKMesh::GetFaceVertexIndex(int Index, int& Vertex1, int& Vertex2, int& Vertex3) {
	JUMPV(0xfc);
}

NAKED CKMaterial* CKMesh::GetFaceMaterial(int Index) {
	JUMPV(0x100);
}

NAKED const VxVector& CKMesh::GetFaceNormal(int Index) {
	JUMPV(0x104);
}

NAKED CKWORD CKMesh::GetFaceChannelMask(int FaceIndex) {
	JUMPV(0x108);
}

NAKED VxVector& CKMesh::GetFaceVertex(int FaceIndex, int VIndex) {
	JUMPV(0x10c);
}

NAKED BYTE* CKMesh::GetFaceNormalsPtr(CKDWORD* Stride) {
	JUMPV(0x110);
}

NAKED void CKMesh::SetFaceVertexIndex(int FaceIndex, int Vertex1, int Vertex2, int Vertex3) {
	JUMPV(0x114);
}

NAKED void CKMesh::SetFaceMaterial(int FaceIndex, CKMaterial* Mat) {
	JUMPV(0x11c);
}

NAKED void CKMesh::SetFaceMaterial(int* FaceIndices, int FaceCount, CKMaterial* Mat) {
	JUMPV(0x120);
}

NAKED void CKMesh::ReplaceMaterial(CKMaterial* oldMat, CKMaterial* newMat, CKBOOL Merge) {
	JUMPV(0x124);
}

NAKED void CKMesh::ApplyGlobalMaterial(CKMaterial* Mat) {
	JUMPV(0x12c);
}

NAKED void CKMesh::DissociateAllFaces() {
	JUMPV(0x130);
}

NAKED CKBOOL CKMesh::SetLineCount(int Count) {
	JUMPV(0x134);
}

NAKED int CKMesh::GetLineCount() {
	JUMPV(0x138);
}

NAKED CKWORD* CKMesh::GetLineIndices() {
	JUMPV(0x13c);
}

NAKED void CKMesh::SetLine(int LineIndex, int VIndex1, int VIndex2) {
	JUMPV(0x140);
}

NAKED void CKMesh::GetLine(int LineIndex, int* VIndex1, int* VIndex2) {
	JUMPV(0x144);
}

NAKED void CKMesh::CreateLineStrip(int StartingLine, int Count, int StartingVertexIndex) {
	JUMPV(0x148);
}

NAKED void CKMesh::Clean(CKBOOL KeepVertices) {
	JUMPV(0x14c);
}

NAKED void CKMesh::InverseWinding() {
	JUMPV(0x150);
}

NAKED void CKMesh::Consolidate() {
	JUMPV(0x154);
}

NAKED void CKMesh::UnOptimize() {
	JUMPV(0x158);
}

NAKED float CKMesh::GetRadius() {
	JUMPV(0x15c);
}

NAKED const VxBbox& CKMesh::GetLocalBox() {
	JUMPV(0x160);
}

NAKED void CKMesh::GetBaryCenter(VxVector* Vector) {
	JUMPV(0x164);
}

NAKED int CKMesh::GetChannelCount() {
	JUMPV(0x168);
}

NAKED int CKMesh::AddChannel(CKMaterial* Mat, CKBOOL CopySrcUv) {
	JUMPV(0x16c);
}

NAKED void CKMesh::RemoveChannel(CKMaterial* Mat) {
	JUMPV(0x170);
}

NAKED void CKMesh::RemoveChannel(int Index) {
	JUMPV(0x174);
}

NAKED int CKMesh::GetChannelByMaterial(CKMaterial* mat) {
	JUMPV(0x178);
}

NAKED void CKMesh::ActivateChannel(int Index, CKBOOL Active) {
	JUMPV(0x17c);
}

NAKED CKBOOL CKMesh::IsChannelActive(int Index) {
	JUMPV(0x180);
}

NAKED void CKMesh::ActivateAllChannels(CKBOOL Active) {
	JUMPV(0x184);
}

NAKED void CKMesh::LitChannel(int Index, CKBOOL Lit) {
	JUMPV(0x188);
}

NAKED CKBOOL CKMesh::IsChannelLit(int Index) {
	JUMPV(0x18c);
}

NAKED CKDWORD CKMesh::GetChannelFlags(int Index) {
	JUMPV(0x190);
}

NAKED void CKMesh::SetChannelFlags(int Index, CKDWORD Flags) {
	JUMPV(0x194);
}

NAKED CKMaterial* CKMesh::GetChannelMaterial(int Index) {
	JUMPV(0x198);
}

NAKED VXBLEND_MODE CKMesh::GetChannelSourceBlend(int Index) {
	JUMPV(0x19c);
}

NAKED VXBLEND_MODE CKMesh::GetChannelDestBlend(int Index) {
	JUMPV(0x1a0);
}

NAKED void CKMesh::SetChannelMaterial(int Index, CKMaterial* Mat) {
	JUMPV(0x1a4);
}

NAKED void CKMesh::SetChannelSourceBlend(int Index, VXBLEND_MODE BlendMode) {
	JUMPV(0x1a8);
}

NAKED void CKMesh::SetChannelDestBlend(int Index, VXBLEND_MODE BlendMode) {
	JUMPV(0x1ac);
}

NAKED void CKMesh::BuildNormals() {
	JUMPV(0x1b0);
}

NAKED void CKMesh::BuildFaceNormals() {
	JUMPV(0x1b4);
}

NAKED CKERROR CKMesh::Render(CKRenderContext* Dev, CK3dEntity* Mov) {
	JUMPV(0x1b8);
}

NAKED CKBOOL CKMesh::AddPreRenderCallBack(CK_MESHRENDERCALLBACK Function, void* Argument, BOOL Temporary) {
	JUMPV(0x1bc);
}

NAKED CKBOOL CKMesh::RemovePreRenderCallBack(CK_MESHRENDERCALLBACK Function, void* Argument) {
	JUMPV(0x1c0);
}

NAKED CKBOOL CKMesh::AddPostRenderCallBack(CK_MESHRENDERCALLBACK Function, void* Argument, BOOL Temporary) {
	JUMPV(0x1c4);
}

NAKED CKBOOL CKMesh::RemovePostRenderCallBack(CK_MESHRENDERCALLBACK Function, void* Argument) {
	JUMPV(0x1c8);
}

NAKED void CKMesh::SetRenderCallBack(CK_MESHRENDERCALLBACK Function, void* Argument) {
	JUMPV(0x1cc);
}

NAKED void CKMesh::SetDefaultRenderCallBack() {
	JUMPV(0x1d0);
}

NAKED void CKMesh::RemoveAllCallbacks() {
	JUMPV(0x1d4);
}

NAKED int CKMesh::GetMaterialCount() {
	JUMPV(0x1d8);
}

NAKED CKMaterial* CKMesh::GetMaterial(int index) {
	JUMPV(0x1dc);
}

NAKED int CKMesh::GetVertexWeightsCount() {
	JUMPV(0x1e0);
}

NAKED void CKMesh::SetVertexWeightsCount(int count) {
	JUMPV(0x1e4);
}

NAKED float* CKMesh::GetVertexWeightsPtr() {
	JUMPV(0x1e8);
}

NAKED float CKMesh::GetVertexWeight(int index) {
	JUMPV(0x1ec);
}

NAKED void CKMesh::SetVertexWeight(int index, float w) {
	JUMPV(0x1f0);
}

NAKED void CKMesh::LoadVertices(CKStateChunk* chunk) {
	JUMPV(0x1f4);
}

NAKED void CKMesh::SetVerticesRendered(int count) {
	JUMPV(0x1f8);
}

NAKED int CKMesh::GetVerticesRendered() {
	JUMPV(0x1fc);
}

NAKED CKERROR CKMesh::CreatePM() {
	JUMPV(0x200);
}

NAKED void CKMesh::DestroyPM() {
	JUMPV(0x204);
}

NAKED CKBOOL CKMesh::IsPM() {
	JUMPV(0x208);
}

NAKED void CKMesh::EnablePMGeoMorph(CKBOOL enable) {
	JUMPV(0x20c);
}

NAKED CKBOOL CKMesh::IsPMGeoMorphEnabled() {
	JUMPV(0x210);
}

NAKED void CKMesh::SetPMGeoMorphStep(int gs) {
	JUMPV(0x214);
}

NAKED int CKMesh::GetPMGeoMorphStep() {
	JUMPV(0x218);
}

NAKED CKBOOL CKMesh::AddSubMeshPreRenderCallBack(CK_SUBMESHRENDERCALLBACK Function, void* Argument, BOOL Temporary) {
	JUMPV(0x21c);
}

NAKED CKBOOL CKMesh::RemoveSubMeshPreRenderCallBack(CK_SUBMESHRENDERCALLBACK Function, void* Argument) {
	JUMPV(0x220);
}

NAKED CKBOOL CKMesh::AddSubMeshPostRenderCallBack(CK_SUBMESHRENDERCALLBACK Function, void* Argument, BOOL Temporary) {
	JUMPV(0x224);
}

NAKED CKBOOL CKMesh::RemoveSubMeshPostRenderCallBack(CK_SUBMESHRENDERCALLBACK Function, void* Argument) {
	JUMPV(0x228);
}

NAKED void CKMesh::SetChannelFaceIndices(int Index, int IndexCount, WORD* Indices) {
	JUMPV(0x22c);
}

NAKED int CKMesh::MapPMVertex(int vertex) {
	JUMPV(0x230);
}

NAKED int CKMesh::AddChannelExt(CKMaterial* Mat, CKBOOL CopySrcUv, ChannelType ChanType) {
	JUMPV(0x234);
}

NAKED ChannelType CKMesh::GetChannelType(int ChanIndex) {
	JUMPV(0x238);
}

NAKED void CKMesh::SetChannelType(int ChanIndex, ChannelType ChanType, BOOL ForceReallocation) {
	JUMPV(0x23c);
}

NAKED void CKMesh::SetVertexData(int Index, int ChanIndex, void* src) {
	JUMPV(0x240);
}

NAKED void CKMesh::GetVertexData(int Index, int ChanIndex, void* dest) {
	JUMPV(0x244);
}
