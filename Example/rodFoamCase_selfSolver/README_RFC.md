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

注意：问题详解见pdf文档。

实现步骤：<br>




案例<br>


备注：implementParabolicVelocityFixedValueBoundaryCondition 为原版教程