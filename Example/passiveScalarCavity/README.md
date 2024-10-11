Title: Implement a passive scalar transport solver
标题：实现被动标量传输求解器

文件结构：
passiveScalarPimpleFoam：标量传输求解器
    Make
    │   ├── files
    │   └── options
    ├── createFields.H
    └── passiveScalarIcoFoam.C

passiveScalarPitzDaily：运行实例
    case
    │   ├── 0
    │   │   ├── U
    │   │   ├── p
    │   │   └── s
    │   ├── cavity.OpenFOAM
    │   ├── constant
    │   │   ├── polyMesh
    │   │   │   ├── boundary
    │   │   │   ├── faces
    │   │   │   ├── neighbour
    │   │   │   ├── owner
    │   │   │   └── points
    │   │   └── transportProperties
    │   └── system
    │       ├── blockMeshDict
    │       ├── controlDict
    │       ├── fvSchemes
    │       ├── fvSolution
    │       └── setFieldsDict

实现步骤：
求解器
1. 被动标量传输方程：$\frac{\partial s}{\partial t}+\nabla\cdot(\mathbf{u}\mathrm{~}s)=0$
2. 根据以下条件修改求解器：1) 在 createFields.H 中读取 volumeScalarField s (参考p); 2) 在 passiveScalarIcoFoam.C 中的 runTime.write() 语句前添加方程 solve(fvm::ddt(s) + fvm::div(phi, s));
3. 修改Make/files 和 Make/options, 用 wmake 命令编译 passiveScalarIcoFoam

案例
1. 在 0 文件夹中创建 s 文件（可参考p文件）
2. fvScheme 中添加s字段的离散化指标 div(phi,s) Gauss linearUpwind grad(U)
3. fvSolution 中添加s字段的求解方法 smoothSolver (参考U)
4. 设置s字段的区域：1) 添加 setFields 文件，并设置其他区域默认值为 0, box内值为 1; 
5. 运行案例

备注：implementPassiveScalarTransportSolver.pdf 为原版教程

