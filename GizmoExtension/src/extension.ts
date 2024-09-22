import * as vscode from 'vscode';
import * as cp from 'child_process';
import * as path from 'path';

export function activate(context: vscode.ExtensionContext) 
{
	const executablePath = path.join(__dirname, '../gizmoCompilerDebug/net8.0/Gizmo.exe');

	const disposable = vscode.commands.registerCommand('Gizmo.Compile', () => {

        const workspaceRoot = vscode.workspace.workspaceFolders?.at(0)?.uri.fsPath;
		const gizmoProjectFilePath = workspaceRoot + "\\project.gizmo";
        vscode.window.showInformationMessage("project file path: " + gizmoProjectFilePath);
        const childProcess = cp.spawn(executablePath, [gizmoProjectFilePath]);

        childProcess.stdout.on('data', (data) => {
            console.log(`stdout: ${data}`);
            vscode.window.showInformationMessage('Compilation output: ' + data.toString());
        });

        childProcess.stderr.on('data', (data) => 
        {
            console.error(`stderr: ${data}`);
            // Handle any errors from the C++ executable
            vscode.window.showErrorMessage('Compilation error: ' + data.toString());
        });

        childProcess.on('close', (code) => 
        {
            console.log(`child process exited with code ${code}`);

            if (code === 0) 
            {
                vscode.window.showInformationMessage('Compilation successful!');

                const terminal = vscode.window.createTerminal('My Terminal');
                terminal.sendText('g++ cppProject/main.cpp -o cppProject/build/main.exe');
                terminal.sendText('start cppProject/build/main.exe');
                terminal.show();
            } 
            else 
            {
                vscode.window.showErrorMessage('Compilation failed.');
            }
        });
	});

	context.subscriptions.push(disposable);
}

// This method is called when your extension is deactivated
export function deactivate() {}
