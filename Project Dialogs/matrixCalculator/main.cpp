//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2016 Media Design School
//
// File Name	: 
// Description	: 
// Author		: Jack Mair : Lance Chaney
// Mail			: jack.mair@mediadesign.school.nz : lance.chaney@mediadesign.school.nz
//


#define WIN32_LEAN_AND_MEAN
#define NOMINMAX

#include <windows.h>   // Include all the windows headers.
#include <windowsx.h>  // Include useful macros.

#include "utils.h"
#include "resource.h"
#include "MatrixCalculator.h"
#include "TransformationCalculator.h"
#include "QuaternionCalculator.h"
#include "SlerpCalculator.h"
#include "GaussianCalculator.h"

#define WINDOW_CLASS_NAME L"WINCLASS1"

HMENU g_hMenu;
HWND g_hDlgMatrix, g_hDlgTransformation, g_hDlgGaussian, g_hDlgQuaternion, g_hDlgSLERP;

void GameLoop()
{
	//One frame of game logic occurs here...
}

LRESULT CALLBACK WindowProc(HWND _hwnd,
	UINT _msg,
	WPARAM _wparam,
	LPARAM _lparam)
{
	// This is the main message handler of the system.
	PAINTSTRUCT ps; // Used in WM_PAINT.
	HDC hdc;        // Handle to a device context.

	// What is the message?
	switch (_msg)
	{
	case WM_CREATE:
	{
		// Do initialization stuff here.

		// Return Success.
		return (0);
	}
		break;

	case WM_PAINT:
	{
		// Simply validate the window.
		hdc = BeginPaint(_hwnd, &ps);

		// You would do all your painting here...

		EndPaint(_hwnd, &ps);

		// Return Success.
		return (0);
	}
		break;

	case WM_COMMAND:
	{
		switch (LOWORD(_wparam))
		{
		case ID_EXIT:
		{
			PostQuitMessage(0);
			break;
		}
		case ID_CALCULATOR_MATRIX:
		{
			ShowWindow(g_hDlgMatrix, SW_SHOWNORMAL);
			break;
		}
		case ID_CALCULATOR_TRANSFORMATION:
		{
			ShowWindow(g_hDlgTransformation, SW_SHOWNORMAL);
			break;

		}
			//open the matrix dialog
		case ID_CALCULATOR_GAUSSIAN:
		{
			ShowWindow(g_hDlgGaussian, SW_SHOWNORMAL);
			break;
		}
			//open the gaussian dialog
		case ID_CALCULATOR_QUATERNION:
		{
			ShowWindow(g_hDlgQuaternion, SW_SHOWNORMAL);
			break;
		}
			//open the quaternion dialog
		case ID_CALCULATOR_SLERP:
		{
			ShowWindow(g_hDlgSLERP, SW_SHOWNORMAL);
			break;
		}
		default:
			break;
		}
		return(0);
	}
		break;

	case WM_DESTROY:
	{
		// Kill the application, this sends a WM_QUIT message.
		PostQuitMessage(0);

		// Return success.
		return (0);
	}
		break;

	default:break;
	} // End switch.

	// Process any messages that we did not take care of...

	return (DefWindowProc(_hwnd, _msg, _wparam, _lparam));
}

BOOL CALLBACK MatrixDlgProc(HWND _hwnd,
	UINT _msg,
	WPARAM _wparam,
	LPARAM _lparam)
{
	static float _value;
	switch (_msg)
	{
	case WM_COMMAND:
	{
		static CMatrixCalculator s_matrixCalculator;
		switch (LOWORD(_wparam))
		{
		case IDC_EDIT_A11:
		{
			_value = ReadFromEditBox(_hwnd, IDC_EDIT_A11);
			break;
		}
		//Add A and B
		case IDOK:
		{
			s_matrixCalculator.AddMatrices(_hwnd);
			break;
		}
		//Multiply AB
		case IDOK2:
		{
			s_matrixCalculator.MultiplyAB(_hwnd);
			break;
		}
		//Subtract B from A
		case IDCANCEL:
		{
			s_matrixCalculator.SubtractMatrices(_hwnd);
			break;
		}
		//Inverse A
		case IDCANCEL2:
		{
			s_matrixCalculator.InverseofA(_hwnd);
			break;
		}
		//Inverse B
		case IDCANCEL3:
		{
			s_matrixCalculator.InverseofB(_hwnd);
			break;
		}
		//Determinant of A
		case IDOK3:
		{
			s_matrixCalculator.DeterminantofA(_hwnd);
			break;
		}
		
		//Set A to Identity
		case IDOK4:
		{
			s_matrixCalculator.HandleSetAtoI(_hwnd);
			break;
		}
		//Multiply BA
		case IDOK5:
		{
			s_matrixCalculator.MultiplyBA(_hwnd);
			break;
		}
		//Multiply A by Scalar
		case IDOK6:
		{
			s_matrixCalculator.ScalarMultiplyA(_hwnd, ReadFromEditBox(_hwnd, IDC_EDIT_AScaled));
			break;
		}
		//Determinant of B
		case IDOK7:
		{
			s_matrixCalculator.DeterminantofB(_hwnd);
			break;
		}
		//Set B to Identity
		case IDOK8:
		{
			s_matrixCalculator.HandleSetBtoI(_hwnd);
			break;
		}

		//transpose A
		case IDOK9:
		{
			s_matrixCalculator.TransposeA(_hwnd);
			break;
		}
		//Multiply B by Scalar
		case IDOK10:
		{
			s_matrixCalculator.ScalarMultiplyB(_hwnd, ReadFromEditBox(_hwnd, IDC_EDIT_BScaled));
			break;
		}
		//transpose B
		case IDOK11:
		{
			s_matrixCalculator.TransposeB(_hwnd);
			break;
		}
		default:
			break;
		}
		return TRUE;
		break;
	}
	case WM_CLOSE:
	{
		MessageBox(_hwnd, ToWideString(_value).c_str(), L"Value in A11", MB_OK);
		ShowWindow(_hwnd, SW_HIDE);
		return TRUE;
		break;
	}
	default:
		break;
	}
	return FALSE;
}

BOOL CALLBACK TransformationDlgProc(HWND _hwnd,
	UINT _msg,
	WPARAM _wparam,
	LPARAM _lparam)
{
	static CTransformationCalculator s_transformationCalculator;
	switch (_msg)
	{
	case WM_COMMAND:
	{
		static CMatrixCalculator s_matrixCalculator;
		switch (LOWORD(_wparam))
		{
		//identity
		case IDC_BUTTON17:
		{
			s_transformationCalculator.HandleSetI(_hwnd);
			break;
		}
		//scale
		case IDC_BUTTON5:
		{
			s_transformationCalculator.ScaleTransformation(_hwnd, ReadFromEditBox(_hwnd, IDC_EDIT1), ReadFromEditBox(_hwnd, IDC_EDIT1), ReadFromEditBox(_hwnd, IDC_EDIT1));
			break;
		}
		//scew
		case IDC_BUTTON16:
		{
			s_transformationCalculator.ScaleTransformation(_hwnd, ReadFromEditBox(_hwnd, IDC_EDIT1), ReadFromEditBox(_hwnd, IDC_EDIT2), ReadFromEditBox(_hwnd, IDC_EDIT3));
			break;
		}
		//translate
		case IDC_BUTTON7:
		{
			s_transformationCalculator.TranslationTransformation(_hwnd, ReadFromEditBox(_hwnd, IDC_EDIT4), ReadFromEditBox(_hwnd, IDC_EDIT5), ReadFromEditBox(_hwnd, IDC_EDIT6));
			break;
		}
		//rotation
		case IDC_BUTTON8:
		{
			s_transformationCalculator.RotationTransformation(_hwnd, ReadFromEditBox(_hwnd, IDC_EDIT7), ReadFromEditBox(_hwnd, IDC_EDIT28), ReadFromEditBox(_hwnd, IDC_EDIT30), ReadFromEditBox(_hwnd, IDC_EDIT13));
			break;
		}
		//reflection
		case IDC_BUTTON18:
		{
			s_transformationCalculator.ReflectionTransformation(_hwnd, ReadFromEditBox(_hwnd, IDC_EDIT32), ReadFromEditBox(_hwnd, IDC_EDIT34), ReadFromEditBox(_hwnd, IDC_EDIT35));
			break;
		}
		//projection
		case IDC_BUTTON9:
		{
			s_transformationCalculator.ProjectionTransformation(_hwnd, ReadFromEditBox(_hwnd, IDC_EDIT14), ReadFromEditBox(_hwnd, IDC_EDIT29), ReadFromEditBox(_hwnd, IDC_EDIT31), ReadFromEditBox(_hwnd, IDC_EDIT15));
			break;
		}
		default:
			break;
		}
		return TRUE;
		break;
	}
	case WM_CLOSE:
	{
		ShowWindow(_hwnd, SW_HIDE);
		return TRUE;
		break;
	}
	default:
		break;
	}
	return FALSE;
}


BOOL CALLBACK GaussianDlgProc(HWND _hwnd,
	UINT _msg,
	WPARAM _wparam,
	LPARAM _lparam)
{
	static CGaussianCalculator s_gaussianCalculator;

	switch (_msg)
	{
	case WM_COMMAND:
	{
		switch (LOWORD(_wparam))
		{
		case IDC_BUTTON1:
		{
			s_gaussianCalculator.HandleBtnApplyRowMultiply(_hwnd);
			break;
		}
		case IDC_BUTTON2:
		{
			s_gaussianCalculator.HandleBtnApplyRowSwap(_hwnd);
			break;
		}
		case IDC_BUTTON3:
		{
			s_gaussianCalculator.HandleBtnApplyAddMultipleOfRowToRow(_hwnd);
			break;
		}
		case IDC_BTNSOLVERE:
		{
			s_gaussianCalculator.HandleBtnRowEchelon(_hwnd);
			break;
		}
		default:
			break;
		}

		return TRUE;
		break;
	}
	case WM_CLOSE:
	{
		ShowWindow(_hwnd, SW_HIDE);
		return TRUE;
		break;
	}
	default:
		break;
	}
	return FALSE;
}


BOOL CALLBACK QuaternionDlgProc(HWND _hwnd,
	UINT _msg,
	WPARAM _wparam,
	LPARAM _lparam)
{
	static CQuaternionCalculator s_quaternionCalculator(_hwnd);

	switch (_msg)
	{
	case WM_COMMAND:
	{
		switch (LOWORD(_wparam))
		{
		case IDC_BUTTON1:
		{
			s_quaternionCalculator.HandleBtnAPlusB();
			break;
		}
		case IDC_BUTTON5:
		{
			s_quaternionCalculator.HandleBtnAMinusB();
			break;
		}
		case IDC_BUTTON6:
		{
			s_quaternionCalculator.HandleBtnBMinusA();
			break;
		}
		case IDC_BUTTON2:
		{
			s_quaternionCalculator.HandleBtnATimesB();
			break;
		}
		case IDC_BUTTON7:
		{
			s_quaternionCalculator.HandleBtnBTimesA();
			break;
		}
		case IDC_BUTTON8:
		{
			s_quaternionCalculator.HandleBtnADotB();
			break;
		}
		case IDC_BUTTON3:
		{
			s_quaternionCalculator.HandleBtnAConjugate();
			break;
		}
		case IDC_BUTTON9:
		{
			s_quaternionCalculator.HandleBtnBConjugate();
			break;
		}
		case IDC_BUTTON10:
		{
			s_quaternionCalculator.HandleBtnMagnitudeOfA();
			break;
		}
		case IDC_BUTTON11:
		{
			s_quaternionCalculator.HandleBtnMagnitudeOfB();
			break;
		}
		case IDC_BUTTON12:
		{
			s_quaternionCalculator.HandleBtnAInverse();
			break;
		}
		case IDC_BUTTON13:
		{
			s_quaternionCalculator.HandleBtnBInverse();
			break;
		}
		case IDC_BUTTON14:
		{
			s_quaternionCalculator.HandleBtnTTimesA();
			break;
		}
		case IDC_BUTTON15:
		{
			s_quaternionCalculator.HandleBtnTTimesB();
			break;
		}
		default:
			break;
		}

		return TRUE;
		break;
	}
	case WM_CLOSE:
	{
		ShowWindow(_hwnd, SW_HIDE);
		return TRUE;
		break;
	}
	default:
		break;
	}
	return FALSE;
}

BOOL CALLBACK SLERPDlgProc(HWND _hwnd,
	UINT _msg,
	WPARAM _wparam,
	LPARAM _lparam)
{
	static CSlerpCalculator s_slerpCalculator(_hwnd);

	switch (_msg)
	{
	case WM_COMMAND:
	{
		switch (LOWORD(_wparam))
		{
		case IDC_BUTTON1:
		{
			s_slerpCalculator.HandleBtnASlerpB();
			break;
		}
		case IDC_BUTTON2:
		{
			s_slerpCalculator.ConvertToMatrix(s_slerpCalculator.GetAQuaternion());
			break;
		}
		case IDC_BUTTON3:
		{
			s_slerpCalculator.ConvertToMatrix(s_slerpCalculator.GetBQuaternion());
			break;
		}
		case IDC_BUTTON4:
		{
			s_slerpCalculator.ConvertToMatrix(s_slerpCalculator.GetRQuaternion());
			break;
		}
		default:
			break;
		}
		return TRUE;
		break;
	}
	case WM_CLOSE:
	{
		ShowWindow(_hwnd, SW_HIDE);
		return TRUE;
		break;
	}
	default:
		break;
	}
	return FALSE;
}

int WINAPI WinMain(HINSTANCE _hInstance,
	HINSTANCE _hPrevInstance,
	LPSTR _lpCmdLine,
	int _nCmdShow)
{
	WNDCLASSEX winclass; // This will hold the class we create.
	HWND hwnd;           // Generic window handle.
	MSG msg;             // Generic message.

	// First fill in the window class structure.
	winclass.cbSize = sizeof(WNDCLASSEX);
	winclass.style = CS_DBLCLKS | CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
	winclass.lpfnWndProc = WindowProc;
	winclass.cbClsExtra = 0;
	winclass.cbWndExtra = 0;
	winclass.hInstance = _hInstance;
	winclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	winclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	winclass.hbrBackground =
		static_cast<HBRUSH>(GetStockObject(BLACK_BRUSH));
	winclass.lpszMenuName = NULL;
	winclass.lpszClassName = WINDOW_CLASS_NAME;
	winclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	// register the window class
	if (!RegisterClassEx(&winclass))
	{
		return (0);
	}

	//Laod the Menu
	g_hMenu = LoadMenu(_hInstance, MAKEINTRESOURCE(IDR_MENU1));

	// create the window
	hwnd = CreateWindowEx(NULL, // Extended style.
		WINDOW_CLASS_NAME,      // Class.
		L"Your Basic Window",   // Title.
		WS_OVERLAPPEDWINDOW | WS_VISIBLE,
		0, 0,                    // Initial x,y.
		400, 100,                // Initial width, height.
		NULL,                   // Handle to parent.
		g_hMenu,                   // Handle to menu.
		_hInstance,             // Instance of this application.
		NULL);                  // Extra creation parameters.

	if (!(hwnd))
	{
		return (0);
	}

	//Create the modeless dialog boxes for the calculators
	//Matrix Calculator
	g_hDlgMatrix = CreateDialog(_hInstance, MAKEINTRESOURCE(IDD_DialogMatrix), hwnd, MatrixDlgProc);
	g_hDlgTransformation = CreateDialog(_hInstance, MAKEINTRESOURCE(IDD_DialogTransformations), hwnd, TransformationDlgProc);
	g_hDlgGaussian = CreateDialog(_hInstance, MAKEINTRESOURCE(IDD_DialogGaussian), hwnd, GaussianDlgProc);
	g_hDlgQuaternion = CreateDialog(_hInstance, MAKEINTRESOURCE(IDD_DialogQuaternion), hwnd, QuaternionDlgProc);
	g_hDlgSLERP = CreateDialog(_hInstance, MAKEINTRESOURCE(IDD_DialogSLERP), hwnd, SLERPDlgProc);

	// Enter main event loop
	while (true)
	{
		// Test if there is a message in queue, if so get it.
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			// Test if this is a quit.
			if (msg.message == WM_QUIT)
			{
				break;
			}

			if ((g_hDlgMatrix == 0 && g_hDlgTransformation == 0 && g_hDlgGaussian == 0 && g_hDlgQuaternion == 0 && g_hDlgSLERP == 0) ||
				(!IsDialogMessage(g_hDlgMatrix, &msg) && !IsDialogMessage(g_hDlgTransformation, &msg) && !IsDialogMessage(g_hDlgGaussian, &msg) && !IsDialogMessage(g_hDlgQuaternion, &msg) && !IsDialogMessage(g_hDlgSLERP, &msg)))
			{
				// Translate any accelerator keys.
				TranslateMessage(&msg);
				// Send the message to the window proc.
				DispatchMessage(&msg);
			}
		}

		// Main game processing goes here.
		GameLoop(); //One frame of game logic occurs here...
	}

	// Return to Windows like this...
	return (static_cast<int>(msg.wParam));
}


