@echo off
set projectName=%1

if "%projectName%"=="" (
    echo Please provide a project name.
    exit /b 1
)

md %projectName%
cd %projectName%
set projectPath=%cd%

type nul > project.gizmo
type nul > main.giz
md build

echo int var = 1 > main.giz
echo print(var) >> main.giz

echo projectName=%projectName% > project.gizmo
echo path="%projectPath%" >> project.gizmo

cd ..




