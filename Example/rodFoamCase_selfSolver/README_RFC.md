Title:  Implement a simple electromagnetic solver <br>
标题：实施简单的电磁求解器 <br>

文件结构：<br>
solver<br>
└── rodFoam<br>
    ├── Make<br>
    │   ├── files<br>
    │   └── options<br>
    ├── createFields.H<br>
    └── rodFoam.C<br>
case<br>
│   ├── 0_orig<br>
│   │   ├── A<br>
│   │   ├── ElPot<br>
│   │   └── sigma<br>
│   ├── constant<br>
│   │   ├── physicalProperties<br>
│   │   └── polyMesh<br>
│   ├── dynamicCode<br>
│   ├── rodComparisonAxBz.plt<br>
│   └── system<br>
│       ├── blockMeshDict<br>
│       ├── controlDict<br>
│       ├── fvSchemes<br>
│       ├── fvSolution<br>
│       ├── setFieldsDict<br>
│       └── singleGraph<br>

注意：求解器说明详解见pdf文档。<br>

实现步骤：<br>
求解器<br>
1. 创建新求解器模板 foamNewSource App rodFoam<br>
```
|-- Make
|   |-- files
|   |-- options
|-- rodFoam.C
```
2.  rodFoam.C<br>
引入其他功能文件
```
#include "createMesh.H"  //In the OpenFOAM installation
#include "createFields.H" //Must be implemented- see next slides
```
引入控制方程
```
solve ( fvm::laplacian(sigma, ElPot) );
solve ( fvm::laplacian(A)==sigma*muMag*(fvc::grad(ElPot)) );
```
引入控制参数
```
B = fvc::curl(A);
Je =-sigma*(fvc::grad(ElPot));
```
将结果保存
```
runTime++;  
sigma.write();
ElPot.write();
A.write();
B.write();
Je.write();
```
3. 创建求解器用字段文件 createFields.H
读取所需字段值
```
Info<< "Reading physicalProperties\n" << endl;
IOdictionary physicalProperties (……);
dimensionedScalar muMag (……);
Info<< "Reading field sigma\n" << endl;
volScalarField sigma (……);
volScalarField ElPot (……);
Info<< "Reading field A\n" << endl;
volVectorField A (……);
Info << "Calculating magnetic field B \n" << endl;
volVectorField B (……);
volVectorField Je (……)
```
4. 修改Make/files 和 Make/options, 用 wmake 命令编译 rodFoam

案例<br>
注意：边界条件说明详解见pdf文档。<br>
边界条件<br>
1. 修改 0 目录下的A, Elpot, sigma 属性，属性如教程所示即可。
2. 调用求解器 rodFoam即可（省略前处理部分步骤）
3. 后处理部分此处省略说明，有兴趣可阅读教程了解。





备注：implementElectromagneticSolver.pdf 为原版教程