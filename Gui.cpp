#include "Gui.h"
#include "minhook/MinHook.h"
#include "ModLoader.h"
#include "ScriptHelper.h"

InputHook::IsKeyDownFunc InputHook::mIsKeyDown = &InputHook::IsKeyDown, InputHook::mIsKeyToggled = &InputHook::IsKeyToggled;
InputHook::IsKeyUpFunc InputHook::mIsKeyUp = &InputHook::IsKeyUp;
InputHook::GetKeyboardStateFunc InputHook::mGetKeyboardState = &InputHook::GetKeyboardState;
InputHook::GetNumberOfKeyInBufferFunc InputHook::mGetNumberOfKeyInBuffer = &InputHook::GetNumberOfKeyInBuffer;
InputHook::GetKeyFromBufferFunc InputHook::mGetKeyFromBuffer = &InputHook::GetKeyFromBuffer;
InputHook::IsMouseDownFunc InputHook::mIsMouseButtonDown = &InputHook::IsMouseButtonDown, InputHook::mIsMouseClicked = &InputHook::IsMouseClicked, InputHook::mIsMouseToggled = &InputHook::IsMouseToggled;
InputHook::GetMouseButtonsStateFunc InputHook::mGetMouseButtonsState = &InputHook::GetMouseButtonsState;

bool InputHook::m_block = false;
unsigned char InputHook::m_keyboardState[256] = { 0 };
unsigned char InputHook::m_lastKeyboard[256] = { 0 };
Vx2DVector InputHook::m_lastMousePosition;

CKMaterial* m_up = nullptr, * m_over = nullptr, * m_inactive = nullptr, * m_field = nullptr, * m_caret = nullptr, * m_highlight = nullptr;
CKGroup* all_sound = nullptr;
CKSTRING g_text_font = nullptr;
CKSTRING g_avail_fonts[] = { "Microsoft YaHei UI", "Microsoft YaHei" };

CKBOOL InputHook::IsKeyDown(CKDWORD iKey, CKDWORD* oStamp) {
	CKBOOL res = InputHook::oIsKeyDown(iKey, oStamp);
	return m_block ? false : res;
}

CKBOOL InputHook::IsKeyUp(CKDWORD iKey) {
	return m_block ? true : InputHook::oIsKeyUp(iKey);
}

CKBOOL InputHook::IsKeyToggled(CKDWORD iKey, CKDWORD* oStamp) {
	CKBOOL res = InputHook::oIsKeyToggled(iKey, oStamp);
	return m_block ? false : res;
}

unsigned char* InputHook::GetKeyboardState() {
	return m_block ? m_keyboardState : InputHook::oGetKeyboardState();
}

int InputHook::GetNumberOfKeyInBuffer() {
	return m_block ? 0 : InputHook::oGetNumberOfKeyInBuffer();
}

int InputHook::GetKeyFromBuffer(int i, CKDWORD& oKey, CKDWORD* oTimeStamp) {
	return m_block ? NO_KEY : InputHook::oGetKeyFromBuffer(i, oKey, oTimeStamp);
}

CKBOOL InputHook::IsMouseButtonDown(CK_MOUSEBUTTON iButton) {
	return m_block ? false : InputHook::oIsMouseButtonDown(iButton);
}

CKBOOL InputHook::IsMouseClicked(CK_MOUSEBUTTON iButton) {
	return m_block ? false : InputHook::oIsMouseClicked(iButton);
}

CKBOOL InputHook::IsMouseToggled(CK_MOUSEBUTTON iButton) {
	return m_block ? false : InputHook::oIsMouseToggled(iButton);
}

void InputHook::GetMouseButtonsState(CKBYTE oStates[4]) {
	if (m_block)
		memset(oStates, KS_IDLE, sizeof(oStates));
	else InputHook::oGetMouseButtonsState(oStates);
}

void InputHook::GetLastMousePosition(Vx2DVector& position) {
	position = m_lastMousePosition;
}

bool InputHook::IsBlock() {
	return m_block;
}

void InputHook::SetBlock(bool block) {
	m_block = block;
}

void InputHook::Process() {
	memcpy(m_lastKeyboard, InputHook::oGetKeyboardState(), sizeof(m_lastKeyboard));
	InputHook::GetMousePosition(m_lastMousePosition, false);
}

CKBOOL InputHook::IsKeyPressed(CKDWORD iKey) {
	return m_block ? false : oIsKeyPressed(iKey);
}

CKBOOL InputHook::IsKeyReleased(CKDWORD iKey) {
	return m_block ? false : oIsKeyReleased(iKey);
}

CKBOOL InputHook::oIsKeyPressed(CKDWORD iKey) {
	return oIsKeyDown(iKey) && !m_lastKeyboard[iKey];
}

CKBOOL InputHook::oIsKeyReleased(CKDWORD iKey) {
	return oIsKeyUp(iKey) && m_lastKeyboard[iKey];
}

bool InputHook::InitHook() {
	if (MH_CreateHook(reinterpret_cast<LPVOID>(0x24ac12a0),
		*reinterpret_cast<LPVOID*>(&InputHook::mIsKeyDown),
		reinterpret_cast<LPVOID*>(&InputHook::mIsKeyDown)) != MH_OK
		|| MH_EnableHook(reinterpret_cast<LPVOID>(0x24ac12a0)) != MH_OK) {
		return false;
	}

	if (MH_CreateHook(reinterpret_cast<LPVOID>(0x24ac12e0),
		*reinterpret_cast<LPVOID*>(&InputHook::mIsKeyUp),
		reinterpret_cast<LPVOID*>(&InputHook::mIsKeyUp)) != MH_OK
		|| MH_EnableHook(reinterpret_cast<LPVOID>(0x24ac12e0)) != MH_OK) {
		return false;
	}

	if (MH_CreateHook(reinterpret_cast<LPVOID>(0x24ac1310),
		*reinterpret_cast<LPVOID*>(&InputHook::mIsKeyToggled),
		reinterpret_cast<LPVOID*>(&InputHook::mIsKeyToggled)) != MH_OK
		|| MH_EnableHook(reinterpret_cast<LPVOID>(0x24ac1310)) != MH_OK) {
		return false;
	}

	if (MH_CreateHook(reinterpret_cast<LPVOID>(0x24ac1220),
		*reinterpret_cast<LPVOID*>(&InputHook::mGetKeyboardState),
		reinterpret_cast<LPVOID*>(&InputHook::mGetKeyboardState)) != MH_OK
		|| MH_EnableHook(reinterpret_cast<LPVOID>(0x24ac1220)) != MH_OK) {
		return false;
	}

	if (MH_CreateHook(reinterpret_cast<LPVOID>(0x24ac1230),
		*reinterpret_cast<LPVOID*>(&InputHook::mGetNumberOfKeyInBuffer),
		reinterpret_cast<LPVOID*>(&InputHook::mGetNumberOfKeyInBuffer)) != MH_OK
		|| MH_EnableHook(reinterpret_cast<LPVOID>(0x24ac1230)) != MH_OK) {
		return false;
	}

	if (MH_CreateHook(reinterpret_cast<LPVOID>(0x24ac1240),
		*reinterpret_cast<LPVOID*>(&InputHook::mGetKeyFromBuffer),
		reinterpret_cast<LPVOID*>(&InputHook::mGetKeyFromBuffer)) != MH_OK
		|| MH_EnableHook(reinterpret_cast<LPVOID>(0x24ac1240)) != MH_OK) {
		return false;
	}

	if (MH_CreateHook(reinterpret_cast<LPVOID>(0x24ac1360),
		*reinterpret_cast<LPVOID*>(&InputHook::mIsMouseButtonDown),
		reinterpret_cast<LPVOID*>(&InputHook::mIsMouseButtonDown)) != MH_OK
		|| MH_EnableHook(reinterpret_cast<LPVOID>(0x24ac1360)) != MH_OK) {
		return false;
	}

	if (MH_CreateHook(reinterpret_cast<LPVOID>(0x24ac1370),
		*reinterpret_cast<LPVOID*>(&InputHook::mIsMouseClicked),
		reinterpret_cast<LPVOID*>(&InputHook::mIsMouseClicked)) != MH_OK
		|| MH_EnableHook(reinterpret_cast<LPVOID>(0x24ac1370)) != MH_OK) {
		return false;
	}

	if (MH_CreateHook(reinterpret_cast<LPVOID>(0x24ac1390),
		*reinterpret_cast<LPVOID*>(&InputHook::mIsMouseToggled),
		reinterpret_cast<LPVOID*>(&InputHook::mIsMouseToggled)) != MH_OK
		|| MH_EnableHook(reinterpret_cast<LPVOID>(0x24ac1390)) != MH_OK) {
		return false;
	}

	if (MH_CreateHook(reinterpret_cast<LPVOID>(0x24ac13b0),
		*reinterpret_cast<LPVOID*>(&InputHook::mGetMouseButtonsState),
		reinterpret_cast<LPVOID*>(&InputHook::mGetMouseButtonsState)) != MH_OK
		|| MH_EnableHook(reinterpret_cast<LPVOID>(0x24ac13b0)) != MH_OK) {
		return false;
	}

	return true;
}

CKBOOL InputHook::oIsKeyDown(CKDWORD iKey, CKDWORD* oStamp) {
	return (this->*mIsKeyDown)(iKey, oStamp);
}

CKBOOL InputHook::oIsKeyUp(CKDWORD iKey) {
	return (this->*mIsKeyUp)(iKey);
}

CKBOOL InputHook::oIsKeyToggled(CKDWORD iKey, CKDWORD* oStamp) {
	return (this->*mIsKeyToggled)(iKey, oStamp);
}

unsigned char* InputHook::oGetKeyboardState() {
	return (this->*mGetKeyboardState)();
}

int InputHook::oGetNumberOfKeyInBuffer() {
	return (this->*mGetNumberOfKeyInBuffer)();
}

int InputHook::oGetKeyFromBuffer(int i, CKDWORD& oKey, CKDWORD* oTimeStamp) {
	return (this->*mGetKeyFromBuffer)(i, oKey, oTimeStamp);
}

CKBOOL InputHook::oIsMouseButtonDown(CK_MOUSEBUTTON iButton) {
	return (this->*mIsMouseButtonDown)(iButton);
}

CKBOOL InputHook::oIsMouseClicked(CK_MOUSEBUTTON iButton) {
	return (this->*mIsMouseClicked)(iButton);
}

CKBOOL InputHook::oIsMouseToggled(CK_MOUSEBUTTON iButton) {
	return (this->*mIsMouseToggled)(iButton);
}

void InputHook::oGetMouseButtonsState(CKBYTE oStates[4]) {
	(this->*mGetMouseButtonsState)(oStates);
}

namespace BGui {

	NAKED char VxScanCodeToAscii(DWORD scancode, unsigned char keystate[256]) {
		JUMP(0x24284D20);
	}

	Element::Element(CKSTRING name) {
		m_2dentity = static_cast<CK2dEntity*>(ModLoader::m_instance->GetCKContext()
			->CreateObject(CKCID_2DENTITY, name));
		ModLoader::m_instance->GetCKContext()->GetCurrentLevel()->AddObject(m_2dentity);
		m_2dentity->SetHomogeneousCoordinates();
		m_2dentity->EnableClipToCamera(false);
		m_2dentity->EnableRatioOffset(false);
		m_2dentity->SetZOrder(20);
	}

	Element::~Element() {
		ModLoader::m_instance->GetCKContext()->DestroyObject(CKOBJID(m_2dentity));
	}

	Vx2DVector Element::GetPosition() {
		Vx2DVector res;
		m_2dentity->GetPosition(res, true);
		return res;
	}

	void Element::SetPosition(Vx2DVector pos) {
		m_2dentity->SetPosition(pos, true);
	}

	Vx2DVector Element::GetSize() {
		Vx2DVector res;
		m_2dentity->GetSize(res, true);
		return res;
	}

	void Element::SetSize(Vx2DVector size) {
		m_2dentity->SetSize(size, true);
	}

	int Element::GetZOrder() {
		return m_2dentity->GetZOrder();
	}

	void Element::SetZOrder(int z) {
		m_2dentity->SetZOrder(z);
	}

	bool Element::IsVisible() {
		return m_2dentity->IsVisible();
	}

	void Element::SetVisible(bool visible) {
		m_2dentity->Show(visible ? CKSHOW : CKHIDE);
	}

	Text::Text(CKSTRING name) : Element(name) {
		CKContext* ctx = ModLoader::m_instance->GetCKContext();
		m_sprite = static_cast<CKSpriteText*>(ctx->CreateObject(CKCID_SPRITETEXT, name));
		m_sprite->ModifyObjectFlags(CK_OBJECT_NOTTOBELISTEDANDSAVED, 0);
		ctx->GetCurrentLevel()->AddObject(m_sprite);
		m_sprite->SetHomogeneousCoordinates();
		m_sprite->EnableClipToCamera(false);
		m_sprite->EnableRatioOffset(false);
		m_sprite->SetZOrder(20);
		m_sprite->SetTextColor(0xffffffff);
		m_sprite->SetAlign(CKSPRITETEXT_ALIGNMENT(CKSPRITETEXT_VCENTER | CKSPRITETEXT_LEFT));
		m_sprite->SetFont(g_text_font, ctx->GetPlayerRenderContext()->GetHeight() / 85, 400);
	}

	Text::~Text() {
		ModLoader::m_instance->GetCKContext()->DestroyObject(CKOBJID(m_sprite));
	}

	void Text::UpdateFont() {
		CKContext* ctx = ModLoader::m_instance->GetCKContext();
		m_sprite->SetFont(g_text_font, ctx->GetPlayerRenderContext()->GetHeight() / 85, 400);
	}

	Vx2DVector Text::GetPosition() {
		Vx2DVector res;
		m_sprite->GetPosition(res, true);
		return res;
	}

	void Text::SetPosition(Vx2DVector pos) {
		m_sprite->SetPosition(pos, true);
	}

	Vx2DVector Text::GetSize() {
		Vx2DVector res;
		m_sprite->GetSize(res, true);
		return res;
	}

	void Text::SetSize(Vx2DVector size) {
		m_sprite->ReleaseAllSlots();
		m_sprite->Create(int(ModLoader::m_instance->GetRenderContext()->GetWidth() * size.x),
			int(ModLoader::m_instance->GetRenderContext()->GetHeight() * size.y), 32);
		m_sprite->SetSize(size, true);
	}

	int Text::GetZOrder() {
		return m_sprite->GetZOrder();
	}

	void Text::SetZOrder(int z) {
		m_sprite->SetZOrder(z);
	}

	bool Text::IsVisible() {
		return m_sprite->IsVisible();
	}

	void Text::SetVisible(bool visible) {
		m_sprite->Show(visible ? CKSHOW : CKHIDE);
	}

	CKSTRING Text::GetText() {
		return m_sprite->GetText();
	}

	void Text::SetText(CKSTRING text) {
		m_sprite->SetText(text);
	}

	void Text::SetFont(CKSTRING FontName, int FontSize, int Weight, CKBOOL italic, CKBOOL underline) {
		m_sprite->SetFont(FontName, FontSize, Weight, italic, underline);
	}

	void Text::SetAlignment(CKSPRITETEXT_ALIGNMENT align) {
		m_sprite->SetAlign(align);
	}

	CKDWORD Text::GetTextColor() {
		return m_sprite->GetTextColor();
	}

	void Text::SetTextColor(CKDWORD color) {
		m_sprite->SetTextColor(color);
	}

	Panel::Panel(CKSTRING name) : Element(name) {
		m_material = static_cast<CKMaterial*>(ModLoader::m_instance->GetCKContext()
			->CreateObject(CKCID_MATERIAL, (std::string(name) + "_Mat").c_str()));
		ModLoader::m_instance->GetCKContext()->GetCurrentLevel()->AddObject(m_material);
		m_material->EnableAlphaBlend();
		m_material->SetSourceBlend(VXBLEND_SRCALPHA);
		m_material->SetDestBlend(VXBLEND_INVSRCALPHA);
		m_2dentity->SetMaterial(m_material);
		m_2dentity->SetZOrder(0);
	}

	Panel::~Panel() {
		ModLoader::m_instance->GetCKContext()->DestroyObject(CKOBJID(m_material));
	}

	VxColor Panel::GetColor() {
		return m_material->GetDiffuse();
	}

	void Panel::SetColor(VxColor color) {
		m_material->SetDiffuse(color);
	}

	Label::Label(CKSTRING name) : Element(name) {
		m_text2d = ExecuteBB::Create2DText(m_2dentity);
	}

	Label::~Label() {
		ModLoader::m_instance->GetCKContext()->DestroyObject(CKOBJID(m_text2d));
	}

	CKSTRING Label::GetText() {
		return ScriptHelper::GetParamString(m_text2d->GetInputParameter(1)->GetRealSource());
	}

	void Label::SetText(CKSTRING text) {
		ScriptHelper::SetParamString(m_text2d->GetInputParameter(1)->GetRealSource(), text);
	}

	ExecuteBB::FontType Label::GetFont() {
		return ExecuteBB::GetFontType(ScriptHelper::GetParamValue<int>(m_text2d->GetInputParameter(0)->GetRealSource()));
	}

	void Label::SetFont(ExecuteBB::FontType font) {
		ScriptHelper::SetParamValue(m_text2d->GetInputParameter(0)->GetRealSource(), ExecuteBB::GetFont(font));
	}

	void Label::SetAlignment(int align) {
		ScriptHelper::SetParamValue(m_text2d->GetInputParameter(2)->GetRealSource(), align);
	}

	int Label::GetTextFlags() {
		return ScriptHelper::GetParamValue<int>(m_text2d->GetLocalParameter(0));
	}

	void Label::SetTextFlags(int flags) {
		ScriptHelper::SetParamValue(m_text2d->GetLocalParameter(0), flags);
	}

	void Label::SetOffset(Vx2DVector offset) {
		ScriptHelper::SetParamValue(m_text2d->GetInputParameter(4)->GetRealSource(), offset);
	}

	void Label::Process() {
		m_text2d->ActivateInput(0);
		m_text2d->Execute(0);
	}

	Button::Button(CKSTRING name) : Label(name) {
		m_2dentity->UseSourceRect();
	}

	ButtonType Button::GetType() {
		return m_type;
	}

	void Button::SetType(ButtonType type) {
		m_type = type;
		m_2dentity->SetMaterial(m_up);

		switch (type) {
		case BUTTON_NORMAL:
			SetFont(ExecuteBB::GAMEFONT_01);
			SetSize(Vx2DVector(0.3f, 0.0938f));
			m_2dentity->SetSourceRect(VxRect(0.0f, 0.51372f, 1.0f, 0.7451f));
			break;
		case BUTTON_BACK:
			SetFont(ExecuteBB::GAMEFONT_01);
			SetSize(Vx2DVector(0.1875f, 0.0938f));
			m_2dentity->SetSourceRect(VxRect(0.2392f, 0.75294f, 0.8666f, 0.98431f));
			break;
		case BUTTON_SETTING:
			SetFont(ExecuteBB::GAMEFONT_01);
			SetSize(Vx2DVector(0.3f, 0.1f));
			m_2dentity->SetSourceRect(VxRect(0.0f, 0.0f, 1.0f, 0.24706f));
			break;
		case BUTTON_LEVEL:
			SetFont(ExecuteBB::GAMEFONT_03);
			SetSize(Vx2DVector(0.1938f, 0.05f));
			m_2dentity->SetSourceRect(VxRect(0.0f, 0.247f, 0.647f, 0.36863f));
			break;
		case BUTTON_KEY:
			SetFont(ExecuteBB::GAMEFONT_03);
			SetSize(Vx2DVector(0.3f, 0.0396f));
			m_2dentity->SetSourceRect(VxRect(0.0f, 0.40785f, 1.0f, 0.51f));
			break;
		case BUTTON_KEYSEL:
			SetFont(ExecuteBB::GAMEFONT_03);
			SetSize(Vx2DVector(0.1450f, 0.0396f));
			m_2dentity->SetSourceRect(VxRect(0.005f, 0.3804f, 0.4353f, 0.4549f));
			break;
		case BUTTON_SMALL:
			SetFont(ExecuteBB::GAMEFONT_03);
			SetSize(Vx2DVector(0.0700f, 0.0354f));
			m_2dentity->SetSourceRect(VxRect(0.0f, 0.82353f, 0.226f, 0.9098f));
			break;
		case BUTTON_LEFT:
			SetSize(Vx2DVector(0.0363f, 0.0517f));
			m_2dentity->SetSourceRect(VxRect(0.6392f, 0.24706f, 0.78823f, 0.40392f));
			break;
		case BUTTON_RIGHT:
			SetSize(Vx2DVector(0.0363f, 0.0517f));
			m_2dentity->SetSourceRect(VxRect(0.7921f, 0.24706f, 0.9412f, 0.40392f));
			break;
		case BUTTON_PLUS:
			SetSize(Vx2DVector(0.0200f, 0.0267f));
			m_2dentity->SetSourceRect(VxRect(0.88627f, 0.8902f, 0.96863f, 0.97255f));
			break;
		case BUTTON_MINUS:
			SetSize(Vx2DVector(0.0200f, 0.0267f));
			m_2dentity->SetSourceRect(VxRect(0.88627f, 0.77804f, 0.96863f, 0.8594f));
			break;
		}
	}

	bool Button::IsActive() {
		return m_active;
	}

	void Button::SetActive(bool active) {
		m_active = active;
		m_2dentity->SetMaterial(active ? m_up : m_inactive);
	}

	void Button::InvokeCallback() {
		m_callback();
	}

	void Button::SetCallback(std::function<void()> callback) {
		m_callback = callback;
	}

	void Button::OnMouseEnter() {
		if (m_active || m_type == BUTTON_SMALL)
			m_2dentity->SetMaterial(m_over);
	}

	void Button::OnMouseLeave() {
		if (m_active || m_type == BUTTON_SMALL)
			m_2dentity->SetMaterial(m_active ? m_up : m_inactive);
	}

	Input::Input(CKSTRING name) : Label(name) {
		m_2dentity->UseSourceRect();
		ScriptHelper::SetParamObject(m_text2d->GetInputParameter(8)->GetRealSource(), ::m_caret);
		ScriptHelper::SetParamString(m_text2d->GetInputParameter(1)->GetRealSource(), "\b");
	}

	void Input::InvokeCallback(CKDWORD key) {
		m_callback(key);
	}

	void Input::SetCallback(std::function<void(CKDWORD)> callback) {
		m_callback = callback;
	}

	void Input::OnCharTyped(CKDWORD key) {
		bool changed = false;

		switch (key) {
		case CKKEY_BACK:
			if (m_caret > 0) {
				m_text.erase(--m_caret);
				changed = true;
			}
			break;
		case CKKEY_DELETE:
			if (m_caret < m_text.size()) {
				m_text.erase(m_caret);
				changed = true;
			}
			break;
		case CKKEY_LEFT:
			if (m_caret > 0) {
				m_caret--;
				changed = true;
			}
			break;
		case CKKEY_RIGHT:
			if (m_caret < m_text.size()) {
				m_caret++;
				changed = true;
			}
			break;
		case CKKEY_HOME:
			if (m_caret > 0) {
				m_caret = 0;
				changed = true;
			}
			break;
		case CKKEY_END:
			if (m_caret < m_text.size()) {
				m_caret = m_text.size();
				changed = true;
			}
			break;
		case CKKEY_ESCAPE:
		case CKKEY_TAB:
		case CKKEY_RETURN:
		case CKKEY_UP:
		case CKKEY_DOWN:
			InvokeCallback(key);
			break;
		default:
			char c = VxScanCodeToAscii(key, ModLoader::m_instance->GetInputManager()->GetKeyboardState());
			if (c) {
				m_text.insert(m_caret++, 1, c);
				changed = true;
			}
		}

		if (changed) {
			InvokeCallback(key);
			std::string caretstr = m_text;
			caretstr.insert(m_caret, 1, '\b');
			ScriptHelper::SetParamString(m_text2d->GetInputParameter(1)->GetRealSource(), caretstr.c_str());
		}
	}

	CKSTRING Input::GetText() {
		return m_text.c_str();
	}

	void Input::SetText(CKSTRING text) {
		m_text = text;
		m_caret = m_text.size();
		ScriptHelper::SetParamString(m_text2d->GetInputParameter(1)->GetRealSource(), (m_text + '\b').c_str());
	}

	void Input::GetFocus() {
		SetTextFlags(GetTextFlags() | TEXT_SHOWCARET);
	}

	void Input::LoseFocus() {
		SetTextFlags(GetTextFlags() & ~TEXT_SHOWCARET);
	}

	KeyInput::KeyInput(CKSTRING name) : Input(name) {
		m_2dentity->UseSourceRect();
		m_2dentity->SetSourceRect(VxRect(0.005f, 0.3804f, 0.4353f, 0.4549f));
	}

	void KeyInput::OnCharTyped(CKDWORD key) {
		SetKey(static_cast<CKKEYBOARD>(key));
		InvokeCallback(key);
	}

	CKKEYBOARD KeyInput::GetKey() {
		return m_key;
	}

	void KeyInput::SetKey(CKKEYBOARD key) {
		m_key = key;
		char name[0x100];
		ModLoader::m_instance->GetInputManager()->GetKeyName(key, name);
		SetText(name);
	}

	void KeyInput::GetFocus() {
		m_2dentity->SetMaterial(m_highlight);
	}

	void KeyInput::LoseFocus() {
		m_2dentity->SetMaterial(nullptr);
	}

	Gui::Gui() {
		CKRenderContext* rc = ModLoader::m_instance->GetRenderContext();
		m_width = rc->GetWidth();
		m_height = rc->GetHeight();
	}

	void Gui::OnCharTyped(CKDWORD key) {
		if (key == CKKEY_ESCAPE)
			if (m_back)
				m_back->InvokeCallback();
		if (m_focus && m_focus->IsVisible())
			m_focus->OnCharTyped(key);
	}

	void Gui::OnMouseDown(float x, float y, CK_MOUSEBUTTON key) {
		if (key == CK_MOUSEBUTTON_LEFT) {
			bool success = false;
			for (Button* button : m_buttons) {
				if (intersect(x, y, button)) {
					button->InvokeCallback();
					success = true;
				}
			}
			if (m_buttons.empty() && m_inputs.size() == 1)
				SetFocus(m_inputs[0]);
			else {
				SetFocus(nullptr);
				for (Input* input : m_inputs) {
					if (intersect(x, y, input)) {
						SetFocus(input);
						success = true;
					}
				}
			}

			if (success) {
				CKMessageManager* mm = ModLoader::m_instance->GetMessageManager();
				CKMessageType msg = mm->AddMessageType("Menu_Click");
				mm->SendMessageSingle(msg, all_sound);
			}
		}
	}

	void Gui::OnMouseWheel(float w) {

	}

	void Gui::OnMouseMove(float x, float y, float lx, float ly) {
	}

	bool Gui::intersect(float x, float y, Element* element) {
		Vx2DVector pos = element->GetPosition(), size = element->GetSize();
		return element->IsVisible() && x >= pos.x && x <= pos.x + size.x && y >= pos.y && y <= pos.y + size.y;
	}

	Button* Gui::AddNormalButton(CKSTRING name, CKSTRING text, float yPos, float xPos, std::function<void()> callback) {
		Button* button = new Button(name);
		button->SetText(text);
		button->SetPosition(Vx2DVector(xPos, yPos));
		button->SetCallback(callback);
		button->SetType(BUTTON_NORMAL);
		m_elements.push_back(button);
		m_buttons.push_back(button);
		return button;
	}

	Button* Gui::AddBackButton(CKSTRING name, CKSTRING text, float yPos, float xPos, std::function<void()> callback) {
		Button* button = new Button(name);
		button->SetText(text);
		button->SetPosition(Vx2DVector(xPos, yPos));
		button->SetCallback(callback);
		button->SetType(BUTTON_BACK);
		m_elements.push_back(button);
		m_buttons.push_back(button);
		m_back = button;
		return button;
	}

	Button* Gui::AddSettingButton(CKSTRING name, CKSTRING text, float yPos, float xPos, std::function<void()> callback) {
		Button* button = new Button(name);
		button->SetText(text);
		button->SetPosition(Vx2DVector(xPos, yPos));
		button->SetCallback(callback);
		button->SetType(BUTTON_SETTING);
		m_elements.push_back(button);
		m_buttons.push_back(button);
		return button;
	}

	Button* Gui::AddLevelButton(CKSTRING name, CKSTRING text, float yPos, float xPos, std::function<void()> callback) {
		Button* button = new Button(name);
		button->SetText(text);
		button->SetPosition(Vx2DVector(xPos, yPos));
		button->SetCallback(callback);
		button->SetType(BUTTON_LEVEL);
		m_elements.push_back(button);
		m_buttons.push_back(button);
		return button;
	}

	Button* Gui::AddSmallButton(CKSTRING name, CKSTRING text, float yPos, float xPos, std::function<void()> callback) {
		Button* button = new Button(name);
		button->SetText(text);
		button->SetPosition(Vx2DVector(xPos, yPos));
		button->SetCallback(callback);
		button->SetType(BUTTON_SMALL);
		m_elements.push_back(button);
		m_buttons.push_back(button);
		return button;
	}

	Button* Gui::AddLeftButton(CKSTRING name, float yPos, float xPos, std::function<void()> callback) {
		Button* button = new Button(name);
		button->SetPosition(Vx2DVector(xPos, yPos));
		button->SetCallback(callback);
		button->SetType(BUTTON_LEFT);
		m_elements.push_back(button);
		m_buttons.push_back(button);
		return button;
	}

	Button* Gui::AddRightButton(CKSTRING name, float yPos, float xPos, std::function<void()> callback) {
		Button* button = new Button(name);
		button->SetPosition(Vx2DVector(xPos, yPos));
		button->SetCallback(callback);
		button->SetType(BUTTON_RIGHT);
		m_elements.push_back(button);
		m_buttons.push_back(button);
		return button;
	}

	Button* Gui::AddPlusButton(CKSTRING name, float yPos, float xPos, std::function<void()> callback) {
		Button* button = new Button(name);
		button->SetPosition(Vx2DVector(xPos, yPos));
		button->SetCallback(callback);
		button->SetType(BUTTON_PLUS);
		m_elements.push_back(button);
		m_buttons.push_back(button);
		return button;
	}

	Button* Gui::AddMinusButton(CKSTRING name, float yPos, float xPos, std::function<void()> callback) {
		Button* button = new Button(name);
		button->SetPosition(Vx2DVector(xPos, yPos));
		button->SetCallback(callback);
		button->SetType(BUTTON_MINUS);
		m_elements.push_back(button);
		m_buttons.push_back(button);
		return button;
	}

	Button* Gui::AddKeyBgButton(CKSTRING name, float yPos, float xPos) {
		Button* button = new Button(name);
		button->SetPosition(Vx2DVector(xPos, yPos));
		button->SetType(BUTTON_KEY);
		m_elements.push_back(button);
		m_buttons.push_back(button);
		return button;
	}

	Panel* Gui::AddPanel(CKSTRING name, VxColor color, float xPos, float yPos, float xSize, float ySize) {
		Panel* panel = new Panel(name);
		panel->SetColor(color);
		panel->SetPosition(Vx2DVector(xPos, yPos));
		panel->SetSize(Vx2DVector(xSize, ySize));
		m_elements.push_back(panel);
		return panel;
	}

	Label* Gui::AddTextLabel(CKSTRING name, CKSTRING text, ExecuteBB::FontType font, float xPos, float yPos, float xSize, float ySize) {
		Label* label = new Label(name);
		label->SetText(text);
		label->SetFont(font);
		label->SetPosition(Vx2DVector(xPos, yPos));
		label->SetSize(Vx2DVector(xSize, ySize));
		m_elements.push_back(label);
		return label;
	}

	Text* Gui::AddText(CKSTRING name, CKSTRING text, float xPos, float yPos, float xSize, float ySize) {
		Text* txt = new Text(name);
		txt->SetText(text);
		txt->SetPosition(Vx2DVector(xPos, yPos));
		txt->SetSize(Vx2DVector(xSize, ySize));
		m_elements.push_back(txt);
		m_texts.push_back(txt);
		return txt;
	}

	Input* Gui::AddTextInput(CKSTRING name, ExecuteBB::FontType font, float xPos, float yPos, float xSize, float ySize, std::function<void(CKDWORD)> callback) {
		Input* input = new Input(name);
		input->SetFont(font);
		input->SetPosition(Vx2DVector(xPos, yPos));
		input->SetSize(Vx2DVector(xSize, ySize));
		input->SetCallback(callback);
		m_elements.push_back(input);
		m_inputs.push_back(input);
		if (!m_focus) SetFocus(input);
		return input;
	}

	std::pair<Button*, KeyInput*> Gui::AddKeyButton(CKSTRING name, CKSTRING text, float yPos, float xPos, std::function<void(CKDWORD)> callback) {
		Button* bg = AddKeyBgButton(name, yPos, xPos);
		bg->SetText(text);
		bg->SetAlignment(ALIGN_LEFT);
		bg->SetZOrder(15);
		bg->SetOffset(Vx2DVector(ModLoader::m_instance->GetRenderContext()->GetWidth() * 0.03f, 0.0f));
		bg->SetCallback([]() {});
		m_elements.push_back(bg);

		KeyInput* button = new KeyInput(name);
		button->SetFont(ExecuteBB::GAMEFONT_03);
		button->SetPosition(Vx2DVector(xPos + 0.155f, yPos));
		button->SetSize(Vx2DVector(0.1450f, 0.0396f));
		button->SetCallback(callback);
		button->SetZOrder(25);
		m_elements.push_back(button);
		m_inputs.push_back(button);
		return { bg, button };
	}

	std::pair<Button*, Button*> Gui::AddYesNoButton(CKSTRING name, float yPos, float x1Pos, float x2Pos, std::function<void(bool)> callback) {
		Button* yes = AddSmallButton(name, "Yes", yPos, x1Pos);
		Button* no = AddSmallButton(name, "No", yPos, x2Pos);
		yes->SetCallback([callback, yes, no]() { callback(true); yes->SetActive(true); no->SetActive(false); });
		no->SetCallback([callback, yes, no]() { callback(false); yes->SetActive(false); no->SetActive(true); });
		m_elements.push_back(yes);
		m_elements.push_back(no);
		return std::pair<Button*, Button*>(yes, no);
	}

	void Gui::Process() {
		CKRenderContext* rc = ModLoader::m_instance->GetRenderContext();
		if (rc->GetWidth() != m_width || rc->GetHeight() != m_height) {
			m_width = rc->GetWidth();
			m_height = rc->GetHeight();
			OnScreenModeChanged();
		}

		for (Element* element : m_elements)
			element->Process();

		InputHook* input = ModLoader::m_instance->GetInputManager();
		int cnt = (m_block ? input->GetNumberOfKeyInBuffer() : input->oGetNumberOfKeyInBuffer());
		for (int i = 0; i < cnt; i++) {
			CKDWORD key;
			if ((m_block ? input->GetKeyFromBuffer(i, key) : input->oGetKeyFromBuffer(i, key)) == KEY_PRESSED)
				OnCharTyped(key);
		}

		Vx2DVector mousePos, lastPos;
		input->GetMousePosition(mousePos, false);
		for (CK_MOUSEBUTTON button = CK_MOUSEBUTTON_LEFT; button < CK_MOUSEBUTTON_4;
			(*reinterpret_cast<int*>(&button))++) {
			if (m_block ? input->IsMouseClicked(button) : input->oIsMouseClicked(button))
				OnMouseDown(mousePos.x / rc->GetWidth(), mousePos.y / rc->GetHeight(), button);
		}

		for (Button* button : m_buttons)
			button->OnMouseLeave();
		for (Button* button : m_buttons)
			if (intersect(mousePos.x / rc->GetWidth(), mousePos.y / rc->GetHeight(), button)) button->OnMouseEnter();

		VxVector relPos;
		input->GetMouseRelativePosition(relPos);
		input->GetLastMousePosition(lastPos);
		if (relPos.x != 0 && relPos.y != 0)
			OnMouseMove(mousePos.x / rc->GetWidth(), mousePos.y / rc->GetHeight(), lastPos.x / rc->GetWidth(), lastPos.y / rc->GetHeight());
		if (relPos.z != 0)
			OnMouseWheel(relPos.z);
	}

	void Gui::SetVisible(bool visible) {
		for (Element* element : m_elements)
			element->SetVisible(visible);
	}

	bool Gui::CanBeBlocked() {
		return m_block;
	}

	void Gui::SetCanBeBlocked(bool block) {
		m_block = block;
	}

	void Gui::SetFocus(Input* input) {
		if (m_focus) m_focus->LoseFocus();
		m_focus = input;
		if (input) input->GetFocus();
	}

	void Gui::InitMaterials() {
		m_up = ModLoader::m_instance->GetMaterialByName("M_Button_Up");
		m_inactive = ModLoader::m_instance->GetMaterialByName("M_Button_Inactive");
		m_over = ModLoader::m_instance->GetMaterialByName("M_Button_Over");
		m_field = ModLoader::m_instance->GetMaterialByName("M_EntryBG");
		m_caret = ModLoader::m_instance->GetMaterialByName("M_Caret");
		m_highlight = ModLoader::m_instance->GetMaterialByName("M_Keys_Highlight");
		all_sound = ModLoader::m_instance->GetGroupByName("All_Sound");

		CKParameterManager* pm = ModLoader::m_instance->GetParameterManager();
		CKEnumStruct* data = pm->GetEnumDescByType(pm->ParameterGuidToType(CKPGUID_FONTNAME));
		for (CKSTRING avail_font : g_avail_fonts) {
			for (int i = 0; i < data->GetNumEnums(); i++) {
				CKSTRING fontname = data->GetEnumDescription(i);
				if (!strcmp(fontname, avail_font)) {
					g_text_font = avail_font;
					break;
				}
			}

			if (g_text_font)
				break;
		}

		if (!g_text_font)
			g_text_font = "";
	}

	void Gui::OnScreenModeChanged() {
		for (Text* txt : m_texts)
			txt->UpdateFont();
	}
}