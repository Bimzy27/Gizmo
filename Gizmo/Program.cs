using System.Runtime.InteropServices;

class Program
{
    private const string dllPath = @"..\GizmoCompiler.dll";

    [DllImport(dllPath)]
    private static extern void Compile(string projectFilePath);
    
    static void Main(string[] args)
    {
        string altText = "C:/Programming/Gizmo/GizmoTestProject/project.gizmo";
        string input = args.Length > 0 ? args[0] : altText; 
        Compile(input);
    }
}