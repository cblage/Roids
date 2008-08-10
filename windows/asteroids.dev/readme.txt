To create a new project:
(1) Copy the "template" directory (to the same "cglib.dev" directory) and rename it "PROJECT_NAME".
(2) In the "PROJECT_NAME\vs2005" directory, rename "template.vcproj" to "PROJECT_NAME.vcproj"
(3) Open "PROJECT_NAME.vcproj" in a text editor (e.g. notepad) and replace all occurences of "template" by "PROJECT_NAME". Actually, there are only 2 occurences of "template": at line 5 (Name="template") and at line 7 (RootNamespace="template"). Save the file.
(4) Add new project (as an existing project) to the cglib workspace inside vs2005. To do this point to the "PROJECT_NAME\vs2005\PROJECT_NAME.vcproj" file. 
(5) Add your source files to the project. All source files should be in the "PROJECT_NAME\src" directory.