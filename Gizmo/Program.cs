using System.Runtime.InteropServices;

class Program
{
    private const string dllPath = @"..\GizmoCompiler.dll";

    [DllImport(dllPath)]
    private static extern void Compile(string projectFilePath);
    
    static void Main(string[] args)
    {
        string altText = "C:/Programming/GizmoTestProject/project.gizmo";
        Compile(args.Length > 0 ? args[0] : altText);
        Console.WriteLine("Input: " + (args.Length > 0 ? args[0] : "No args"));
    }
}