@echo off

set /p projectName=Enter project name: 
echo You entered: %projectName%

md %projectName%
cd %projectName%
set projectPath=%cd%

type nul > project.gizmo
type nul > main.giz
md cppProject

echo number var = 1 > main.giz
echo writeLine(var) >> main.giz

echo projectName=%projectName% > project.gizmo
echo path=%projectPath% >> project.gizmo
echo main=main.giz >> project.gizmo

cd cppProject
md build