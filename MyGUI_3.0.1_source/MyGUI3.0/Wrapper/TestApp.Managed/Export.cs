using System;
using System.Collections.Generic;
using System.Text;
using System.Runtime.InteropServices;

namespace MyGUI.Managed.Demo
{

    public class Export
    {

        #region Export
#if DEBUG
        [DllImport("WrapperBaseApp_d.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern void ExportDemo_Initialise();
        [DllImport("WrapperBaseApp_d.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern void ExportDemo_AddFrameDelegate(HandleFrameStart _delegate);
        [DllImport("WrapperBaseApp_d.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern void ExportDemo_Run();
        [DllImport("WrapperBaseApp_d.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern void ExportDemo_Shutdown();
        [DllImport("WrapperBaseApp_d.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern void ExportDemo_DebugOut([MarshalAs(UnmanagedType.LPStr)]string _str);
#else
        [DllImport("WrapperBaseApp.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern void ExportDemo_Initialise();
        [DllImport("WrapperBaseApp.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern void ExportDemo_AddFrameDelegate(HandleFrameStart _delegate);
        [DllImport("WrapperBaseApp.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern void ExportDemo_Run();
        [DllImport("WrapperBaseApp.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern void ExportDemo_Shutdown();
        [DllImport("WrapperBaseApp.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern void ExportDemo_DebugOut([MarshalAs(UnmanagedType.LPStr)]string _str);
#endif

        #endregion

        public delegate void HandleFrameStart(float _time);

        public static void Initialise()
        {
            ExportDemo_Initialise();
        }

        public static void AddFrameDelegate(HandleFrameStart _delegate)
        {
            ExportDemo_AddFrameDelegate(_delegate);
        }

        public static void Run()
        {
            ExportDemo_Run();
        }

        public static void Shutdown()
        {
            ExportDemo_Shutdown();
        }

        public static void DebugOut(string _str)
        {
            ExportDemo_DebugOut(_str);
        }

    }

}
