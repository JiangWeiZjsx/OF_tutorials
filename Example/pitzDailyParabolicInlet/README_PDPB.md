Title: Implement a parabolicVelocity fixedValue boundary condition<br>
标题：实现速度呈抛物线的边界条件<br>

文件结构：<br>
pitzDailyParabolicInlet: 抛物线边界条件<br>
boundary<br>
    │   └── parabolicVelocity<br>
    │       ├── Make<br>
    │       │   ├── files<br>
    │       │   └── options<br>
    │       ├── lnInclude<br>
    │       ├── parabolicVelocityFvPatchVectorField.C<br>
    │       └── parabolicVelocityFvPatchVectorField.H<br>

case<br>
    │   ├── 0<br>
    │   │   ├── U<br>
    │   │   ├── epsilon<br>
    │   │   ├── f<br>
    │   │   ├── k<br>
    │   │   ├── nuTilda<br>
    │   │   ├── nut<br>
    │   │   ├── omega<br>
    │   │   ├── p<br>
    │   │   └── v2<br>
    │   ├── constant<br>
    │   │   ├── polyMesh<br>
    │   │   │   ├── boundary<br>
    │   │   │   ├── faces<br>
    │   │   │   ├── neighbour<br>
    │   │   │   ├── owner<br>
    │   │   │   └── points<br>
    │   │   ├── transportProperties<br>
    │   │   └── turbulenceProperties<br>
    │   └── system<br>
    │       ├── blockMeshDict<br>
    │       ├── controlDict<br>
    │       ├── fvSchemes<br>
    │       ├── fvSolution<br>
    │       └── streamlines<br>


实现步骤：<br>
边界条件<br>
1. 创建边界条件模板 foamNewBC -f -v parabolicVelocity, 得到以下文件目录<br>
```
parabolicVelocity 
    ├── Make 
    │   ├── files 
    │   └── options 
    ├── parabolicVelocityFvPatchVectorField.C 
    └── parabolicVelocityFvPatchVectorField.H
```
2. parabolicVelocityFvPatchVectorField.H <br>
创建变量<br>
```
scalar maxValue_;   //- Peak velocity magnitude 
vector n_;   //- Flow direction 
vector y_;  //- Direction of the y-coordinate 
```
创建成员函数<br>
```
scalar& maxValue() { return maxValue_; }  //- Return max value
vector& n() { return n_; }  //- Return flow direction
vector& y() { return y_; } //- Return y direction
```
3. parabolicVelocityFvPatchVectorField.C <br>
初始化构造部分，如<br>
第一个构造器<br>
```
fixedValueFvPatchVectorField(p, iF), 
maxValue_(0), 
n_(1, 0, 0), 
y_(0, 1, 0)
```
第二个构造器<br>
```
fixedValueFvPatchVectorField(p, iF), 
maxValue_(readScalar(dict.lookup("maxValue"))), 
n_(dict.lookup("n")), 
y_(dict.lookup("y"))
```
……<br>
4. 第2个构造器内添加 add 函数<br>
```
Info << "Using the parabolicVelocity boundary condition" << endl; 
if (mag(n_) < SMALL || mag(y_) < SMALL) 
{ 
    FatalErrorIn("parabolicVelocityFvPatchVectorField(dict)") 
    << "n or y given with zero size not correct" 
    << abort(FatalError); 
} 
n_ /= mag(n_); 
y_ /= mag(y_);

```
5. 修改 因子更新函数 updateCoeffs() <br>
```
if (updated()) 
{ return; } 
// Get range and orientation 
boundBox bb(patch().patch().localPoints(), true); 
vector ctr = 0.5*(bb.max() + bb.min()); 
const vectorField& c = patch().Cf(); 
// Calculate local 1-D coordinate for the parabolic profile 
scalarField coord = 2*((c - ctr) & y_)/((bb.max() - bb.min()) & y_); 
vectorField::operator=(n_*maxValue_*(1.0 - sqr(coord)));
```
6. 修改 写函数 write() <br>
7. 修改Make/files 和 Make/options, 用 wmake 命令编译 passiveScalarIcoFoam



案例<br>
1. 修改 0/U 的 inlet 边界条件<br>
```
inlet 
{ 
    type parabolicVelocity; 
    n (1 0 0); 
    y (0 1 0); 
    maxValue 1; 
}
```
2. system/controlDict 链接编译后文件: libs ("libparabolicVelocity.so");<br>

备注：implementParabolicVelocityFixedValueBoundaryCondition 为原版教程