#ifndef MR_GUI_H
#define MR_GUI_H

//lexAddToken(T_LOADPALETTETABLE, "loadpalettetable");
//lexAddToken(T_DISPLAYGFX, "displaygfx");
//lexAddToken(T_SELECTWIN, "selectwin");
//lexAddToken(T_CREATEWIN, "createwin");
//lexAddToken(T_DELETEWIN, "deletewin");
//lexAddToken(T_RESIZEWIN, "resizewin");
//lexAddToken(T_SCALEWIN, "scalewin");
//lexAddToken(T_SHOWWIN, "showwin");
//lexAddToken(T_FILLWIN, "fillwin");
//lexAddToken(T_FILLRECT, "fillrect");
//lexAddToken(T_FILLWIN3X3, "fillwin3x3");
//lexAddToken(T_ADDBUTTON, "addbutton");
//lexAddToken(T_ADDBUTTONTEXT, "addbuttontext");
//lexAddToken(T_ADDBUTTONGFX, "addbuttongfx");
//lexAddToken(T_ADDBUTTONPROC, "addbuttonproc");
//lexAddToken(T_ADDBUTTONFLAG, "addbuttonflag");
//lexAddToken(T_ADDBUTTONRIGHTPROC, "addbuttonrightproc");
//lexAddToken(T_DELETEBUTTON, "deletebutton");

//# Constants #////////////////////////////////////////////////////////////////////////////////////////

#define GUI_Label_Indent_Left (0)
#define GUI_Label_Indent_Right (1)
#define GUI_Label_Indent_Center (2)

//# Macros #///////////////////////////////////////////////////////////////////////////////////////////

#define GUI_Null_Proc \
   __gui_null_proc

#define GUI_Create_Window(Name, X, Y, Width, Height) \
   begin \
      CreateWin(Name, X, Y, Width, Height); \
      SelectWin(Name); \
      FillWin(0.0, 0.0, 0.0); \
      SetFont(5); \
      SetTextColor(0.0, 0.0, 0.0); \
      SetTextFlags(0); \
   end

#define GUI_Show_Window(Name) \
   begin \
      SelectWin(Name); \
      ShowWin; \
   end

#define  GUI_Delete_Window(Name) \
   DeleteWin(Name);

#define GUI_Create_Button(Window_Name, Button_Name, X, Y, Width, Height, Text) \
   begin \
      SelectWin(Window_Name); \
      AddButton(Button_Name, X, Y, Width, Height); \
      AddButtonText(Button_Name, Text); \
   end

#define GUI_Set_Button_Proc(Name, On_Mouse_On_Proc, On_Mouse_Off_Proc, On_Mouse_Press_Proc, On_Mouse_Release_Proc) \
   AddButtonProc(Name, On_Mouse_On_Proc, On_Mouse_Off_Proc, On_Mouse_Press_Proc, On_Mouse_Release_Proc); \
   noop

#define GUI_Set_Button_Release_Proc(Name, On_Mouse_Release_Proc) \
   AddButtonProc(Name, GUI_Null_Proc, GUI_Null_Proc, GUI_Null_Proc, On_Mouse_Release_Proc); 

#define GUI_Delete_Button(Name) \
   DeleteButton(Name);

#define GUI_Create_Label(Window_Name, Text, X, Y, Width, Height, Flags) \
   begin \
      SelectWin(Window_Name); \
      Format(Text, X, Y, Width, Height, Flags); \
   end

//FillRect(X, Y, Width, Height, 1.0, 0.0, 0.0); \

#define GUI_Create_Label_Ex(Window_Name, Text, X, Y, Width, Height, Flags, Red, Green, Blue) \
   begin \
      SelectWin(Window_Name); \
      SetTextColor(Red, Green, Blue); \
      Format(Text, X, Y, Width, Height, Flags); \
      SetTextColor(0.0, 0.0, 0.0); \
   end

#define GUI_Set_Cursor(Path) \
   MouseShape(Path, 0, 0);

#define GUI_Fill_Rect(Window_Name, X, Y, Width, Height, Red, Green, Blue) \
   begin \
      SelectWin(Window_Name); \
      FillRect(X, Y, Width, Height, Red, Green, Blue); \
   end

//# Procedure Declarations #///////////////////////////////////////////////////////////////////////////

// Private procedures

procedure __gui_null_proc;

//# Procedures #///////////////////////////////////////////////////////////////////////////////////////
   
procedure __gui_null_proc
begin
end

#endif // MR_GUI_H
