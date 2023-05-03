#pragma once

struct Control {
	int m_button;
	Control(int button) { m_button = button; m_keyThatShouldNotBePressed = 0; }
	Control(int button, int hax) { m_button = button; m_keyThatShouldNotBePressed = hax; }
	bool Pressed() { return !KeyDown(m_keyThatShouldNotBePressed) && PAD::IsDisabledControlJustPressed(2, m_button); }
	bool Held() { return !KeyDown(m_keyThatShouldNotBePressed) && PAD::IsDisabledControlPressed(2, m_button); }
private:
	int m_keyThatShouldNotBePressed;
};

class Controller {
private:
	vector<Control*> m_buttons ={
		&B, &A,
		&X, &Y,
		&Up, &Down, &Left, &Right,
		&RB, &RT, &LB, &LT,
		&LS, &RS,
	};
public:
	Control B = Control(INPUT_FRONTEND_CANCEL);
	Control A = Control(INPUT_FRONTEND_ACCEPT);
	Control X = Control(INPUT_FRONTEND_X);
	Control Y = Control(INPUT_FRONTEND_Y);

	Control Up = Control(INPUT_FRONTEND_UP);
	Control Down = Control(INPUT_FRONTEND_DOWN);
	Control Left = Control(INPUT_FRONTEND_LEFT);
	Control Right = Control(INPUT_FRONTEND_RIGHT);

	Control RB = Control(INPUT_FRONTEND_RB);
	Control RT = Control(INPUT_FRONTEND_RT);
	Control LB = Control(INPUT_FRONTEND_LB);
	Control LT = Control(INPUT_FRONTEND_LT);

	Control LS = Control(INPUT_FRONTEND_LS, VK_SHIFT);
	Control RS = Control(INPUT_FRONTEND_RS);

	vector<Control*> GetControls() { return m_buttons; }
};

Controller* GetController();