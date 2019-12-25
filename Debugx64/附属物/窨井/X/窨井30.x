xof 0303txt 0032
template ColorRGBA {
 <35ff44e0-6c7c-11cf-8f52-0040333594a3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <d3e16e81-7835-11cf-8f52-0040333594a3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template Material {
 <3d82ab4d-62da-11cf-ab39-0020af71e433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template TextureFilename {
 <a42790e1-7810-11cf-8f52-0040333594a3>
 STRING filename;
}

template Frame {
 <3d82ab46-62da-11cf-ab39-0020af71e433>
 [...]
}

template Matrix4x4 {
 <f6f23f45-7686-11cf-8f52-0040333594a3>
 array FLOAT matrix[16];
}

template FrameTransformMatrix {
 <f6f23f41-7686-11cf-8f52-0040333594a3>
 Matrix4x4 frameMatrix;
}

template Vector {
 <3d82ab5e-62da-11cf-ab39-0020af71e433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template MeshFace {
 <3d82ab5f-62da-11cf-ab39-0020af71e433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template Mesh {
 <3d82ab44-62da-11cf-ab39-0020af71e433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

template MeshNormals {
 <f6f23f43-7686-11cf-8f52-0040333594a3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshMaterialList {
 <f6f23f42-7686-11cf-8f52-0040333594a3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material <3d82ab4d-62da-11cf-ab39-0020af71e433>]
}

template Coords2d {
 <f6f23f44-7686-11cf-8f52-0040333594a3>
 FLOAT u;
 FLOAT v;
}

template MeshTextureCoords {
 <f6f23f40-7686-11cf-8f52-0040333594a3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template Animation {
 <3d82ab4f-62da-11cf-ab39-0020af71e433>
 [...]
}

template AnimationSet {
 <3d82ab50-62da-11cf-ab39-0020af71e433>
 [Animation <3d82ab4f-62da-11cf-ab39-0020af71e433>]
}

template FloatKeys {
 <10dd46a9-775b-11cf-8f52-0040333594a3>
 DWORD nValues;
 array FLOAT values[nValues];
}

template TimedFloatKeys {
 <f406b180-7b3b-11cf-8f52-0040333594a3>
 DWORD time;
 FloatKeys tfkeys;
}

template AnimationKey {
 <10dd46a8-775b-11cf-8f52-0040333594a3>
 DWORD keyType;
 DWORD nKeys;
 array TimedFloatKeys keys[nKeys];
}


Material Material__84 {
 1.000000;1.000000;1.000000;1.000000;;
 3.200000;
 0.000000;0.000000;0.000000;;
 0.000000;0.000000;0.000000;;

 TextureFilename {
  "yinjing30.jpg";
 }
}

Frame yinjing30 {
 

 FrameTransformMatrix {
  1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-0.850000,-0.000000,1.000000;;
 }

 Mesh  {
  124;
  -1.500000;0.000000;-1.500000;,
  1.500000;0.000000;-1.500000;,
  -1.500000;0.000000;1.500000;,
  1.500000;0.000000;1.500000;,
  -1.500000;7.389995;-1.500000;,
  1.500000;7.389995;-1.500000;,
  -1.500000;7.389995;1.500000;,
  1.500000;7.389995;1.500000;,
  -0.186489;7.389995;-0.792922;,
  -0.265534;7.389995;-0.497922;,
  -0.265534;8.450000;-0.497922;,
  -0.186489;8.450000;-0.792922;,
  -0.481489;7.389994;-0.281967;,
  -0.481489;8.450000;-0.281967;,
  -0.776489;7.389994;-0.202923;,
  -0.776489;8.450000;-0.202922;,
  -1.071489;7.389994;-0.281967;,
  -1.071489;8.450000;-0.281967;,
  -1.287444;7.389995;-0.497922;,
  -1.287444;8.450000;-0.497922;,
  -1.366489;7.389995;-0.792922;,
  -1.366489;8.450000;-0.792922;,
  -1.287444;7.389995;-1.087922;,
  -1.287444;8.450000;-1.087922;,
  -1.071489;7.389995;-1.303877;,
  -1.071489;8.450000;-1.303877;,
  -0.776489;7.389994;-1.382922;,
  -0.776489;8.450000;-1.382922;,
  -0.481489;7.389995;-1.303877;,
  -0.481489;8.450000;-1.303877;,
  -0.265534;7.389995;-1.087922;,
  -0.265534;8.450000;-1.087922;,
  -0.434955;8.450000;-0.792922;,
  -0.480712;8.450000;-0.622155;,
  -0.605722;8.450000;-0.497145;,
  -0.776489;8.450000;-0.451389;,
  -0.947256;8.450000;-0.497145;,
  -1.072266;8.450000;-0.622155;,
  -1.118022;8.450000;-0.792922;,
  -1.072266;8.450000;-0.963689;,
  -0.947256;8.450000;-1.088699;,
  -0.776489;8.450000;-1.134456;,
  -0.605722;8.450000;-1.088699;,
  -0.480712;8.450000;-0.963689;,
  1.500000;0.150000;-1.500000;,
  1.500000;7.239995;-1.500000;,
  -1.500000;7.239995;-1.500000;,
  -1.500000;0.150000;-1.500000;,
  1.500000;0.150000;1.500000;,
  1.500000;7.239995;1.500000;,
  -1.500000;0.150000;1.500000;,
  -1.500000;7.239995;1.500000;,
  1.500000;0.150000;-1.500000;,
  1.500000;7.239995;-1.500000;,
  1.500000;0.150000;1.500000;,
  1.500000;7.239995;1.500000;,
  -1.500000;7.239995;-1.500000;,
  -1.500000;0.150000;1.500000;,
  -1.500000;7.239995;1.500000;,
  -1.500000;0.150000;-1.500000;,
  -0.481489;8.450000;-0.281967;,
  -0.481489;7.389994;-0.281967;,
  -1.071489;8.450000;-0.281967;,
  -1.071489;7.389994;-0.281967;,
  -1.071489;8.450000;-1.303877;,
  -1.071489;7.389995;-1.303877;,
  -0.481489;8.450000;-1.303877;,
  -0.481489;7.389995;-1.303877;,
  -0.186489;8.450000;-0.792922;,
  -0.480712;8.450000;-0.622155;,
  -0.265534;8.450000;-0.497922;,
  -0.434955;8.450000;-0.792922;,
  -0.605722;8.450000;-0.497145;,
  -0.481489;8.450000;-0.281967;,
  -0.776489;8.450000;-0.451389;,
  -0.776489;8.450000;-0.202922;,
  -0.947256;8.450000;-0.497145;,
  -1.071489;8.450000;-0.281967;,
  -1.072266;8.450000;-0.622155;,
  -1.287444;8.450000;-0.497922;,
  -1.118022;8.450000;-0.792922;,
  -1.366489;8.450000;-0.792922;,
  -1.072266;8.450000;-0.963689;,
  -1.287444;8.450000;-1.087922;,
  -0.947256;8.450000;-1.088699;,
  -1.071489;8.450000;-1.303877;,
  -0.776489;8.450000;-1.134456;,
  -0.776489;8.450000;-1.382922;,
  -0.605722;8.450000;-1.088699;,
  -0.481489;8.450000;-1.303877;,
  -0.480712;8.450000;-0.963689;,
  -0.265534;8.450000;-1.087922;,
  1.500000;7.389995;-1.500000;,
  -1.500000;7.239995;-1.500000;,
  -1.500000;7.389995;-1.500000;,
  1.500000;7.239995;-1.500000;,
  -1.500000;0.000000;-1.500000;,
  1.500000;0.150000;-1.500000;,
  1.500000;0.000000;-1.500000;,
  -1.500000;0.150000;-1.500000;,
  1.500000;7.389995;1.500000;,
  1.500000;7.239995;-1.500000;,
  1.500000;7.389995;-1.500000;,
  1.500000;7.239995;1.500000;,
  1.500000;0.000000;-1.500000;,
  1.500000;0.150000;1.500000;,
  1.500000;0.000000;1.500000;,
  1.500000;0.150000;-1.500000;,
  -1.500000;7.389995;1.500000;,
  1.500000;7.239995;1.500000;,
  1.500000;7.389995;1.500000;,
  -1.500000;7.239995;1.500000;,
  1.500000;0.000000;1.500000;,
  -1.500000;0.150000;1.500000;,
  -1.500000;0.000000;1.500000;,
  1.500000;0.150000;1.500000;,
  -1.500000;7.389995;-1.500000;,
  -1.500000;7.239995;1.500000;,
  -1.500000;7.389995;1.500000;,
  -1.500000;7.239995;-1.500000;,
  -1.500000;0.000000;1.500000;,
  -1.500000;0.150000;-1.500000;,
  -1.500000;0.000000;-1.500000;,
  -1.500000;0.150000;1.500000;;
  86;
  3;0,3,2;,
  3;3,0,1;,
  3;4,7,5;,
  3;7,4,6;,
  3;45,47,46;,
  3;47,45,44;,
  3;49,52,53;,
  3;52,49,48;,
  3;51,54,55;,
  3;54,51,50;,
  3;56,57,58;,
  3;57,56,59;,
  3;8,10,9;,
  3;10,8,11;,
  3;12,10,13;,
  3;10,12,9;,
  3;14,60,15;,
  3;60,14,61;,
  3;16,15,17;,
  3;15,16,14;,
  3;18,62,19;,
  3;62,18,63;,
  3;20,19,21;,
  3;19,20,18;,
  3;22,21,23;,
  3;21,22,20;,
  3;24,23,25;,
  3;23,24,22;,
  3;26,64,27;,
  3;64,26,65;,
  3;28,27,29;,
  3;27,28,26;,
  3;30,66,31;,
  3;66,30,67;,
  3;8,31,11;,
  3;31,8,30;,
  3;33,35,34;,
  3;35,37,36;,
  3;37,39,38;,
  3;35,39,37;,
  3;39,41,40;,
  3;41,43,42;,
  3;39,43,41;,
  3;35,43,39;,
  3;33,43,35;,
  3;32,43,33;,
  3;68,69,70;,
  3;69,68,71;,
  3;70,72,73;,
  3;72,70,69;,
  3;73,74,75;,
  3;74,73,72;,
  3;75,76,77;,
  3;76,75,74;,
  3;77,78,79;,
  3;78,77,76;,
  3;79,80,81;,
  3;80,79,78;,
  3;81,82,83;,
  3;82,81,80;,
  3;83,84,85;,
  3;84,83,82;,
  3;85,86,87;,
  3;86,85,84;,
  3;87,88,89;,
  3;88,87,86;,
  3;89,90,91;,
  3;90,89,88;,
  3;91,71,68;,
  3;71,91,90;,
  3;92,93,94;,
  3;93,92,95;,
  3;96,97,98;,
  3;97,96,99;,
  3;100,101,102;,
  3;101,100,103;,
  3;104,105,106;,
  3;105,104,107;,
  3;108,109,110;,
  3;109,108,111;,
  3;112,113,114;,
  3;113,112,115;,
  3;116,117,118;,
  3;117,116,119;,
  3;120,121,122;,
  3;121,120,123;;

  MeshNormals  {
   36;
   0.000000;-1.000000;0.000000;,
   0.000000;1.000000;0.000000;,
   0.000000;-0.000000;-1.000000;,
   0.000000;-0.000000;-1.000000;,
   0.000000;-0.000000;-1.000000;,
   0.000000;-0.000000;-1.000000;,
   1.000000;0.000000;0.000000;,
   0.000000;0.000000;1.000000;,
   0.000000;0.000000;1.000000;,
   -1.000000;0.000000;0.000000;,
   1.000000;-0.000000;-0.000001;,
   0.866025;-0.000000;0.500000;,
   0.866025;-0.000000;0.500000;,
   1.000000;0.000000;-0.000001;,
   0.500000;-0.000000;0.866026;,
   0.500000;-0.000000;0.866026;,
   0.000000;-0.000000;1.000000;,
   0.000000;-0.000000;1.000000;,
   -0.500000;-0.000000;0.866026;,
   -0.500000;-0.000000;0.866026;,
   -0.866025;-0.000000;0.500000;,
   -0.866025;-0.000000;0.500000;,
   -1.000000;0.000000;-0.000000;,
   -1.000000;-0.000000;0.000000;,
   -0.866026;-0.000000;-0.500000;,
   -0.866025;0.000000;-0.500000;,
   -0.500000;0.000000;-0.866025;,
   -0.500000;0.000000;-0.866025;,
   -0.000000;0.000000;-1.000000;,
   -0.000000;0.000000;-1.000000;,
   0.500000;0.000000;-0.866026;,
   0.500000;0.000000;-0.866025;,
   0.866025;0.000000;-0.500000;,
   0.866025;-0.000000;-0.500001;,
   0.000000;0.000000;-1.000000;,
   0.000000;0.000000;1.000000;;
   86;
   3;0,0,0;,
   3;0,0,0;,
   3;1,1,1;,
   3;1,1,1;,
   3;2,3,4;,
   3;3,2,5;,
   3;6,6,6;,
   3;6,6,6;,
   3;7,8,7;,
   3;8,7,7;,
   3;9,9,9;,
   3;9,9,9;,
   3;10,11,12;,
   3;11,10,13;,
   3;14,11,15;,
   3;11,14,12;,
   3;16,15,17;,
   3;15,16,14;,
   3;18,17,19;,
   3;17,18,16;,
   3;20,19,21;,
   3;19,20,18;,
   3;22,21,23;,
   3;21,22,20;,
   3;24,23,25;,
   3;23,24,22;,
   3;26,25,27;,
   3;25,26,24;,
   3;28,27,29;,
   3;27,28,26;,
   3;30,29,31;,
   3;29,30,28;,
   3;32,31,33;,
   3;31,32,30;,
   3;10,33,13;,
   3;33,10,32;,
   3;1,1,1;,
   3;1,1,1;,
   3;1,1,1;,
   3;1,1,1;,
   3;1,1,1;,
   3;1,1,1;,
   3;1,1,1;,
   3;1,1,1;,
   3;1,1,1;,
   3;1,1,1;,
   3;1,1,1;,
   3;1,1,1;,
   3;1,1,1;,
   3;1,1,1;,
   3;1,1,1;,
   3;1,1,1;,
   3;1,1,1;,
   3;1,1,1;,
   3;1,1,1;,
   3;1,1,1;,
   3;1,1,1;,
   3;1,1,1;,
   3;1,1,1;,
   3;1,1,1;,
   3;1,1,1;,
   3;1,1,1;,
   3;1,1,1;,
   3;1,1,1;,
   3;1,1,1;,
   3;1,1,1;,
   3;1,1,1;,
   3;1,1,1;,
   3;1,1,1;,
   3;1,1,1;,
   3;34,4,34;,
   3;4,34,2;,
   3;34,5,34;,
   3;5,34,3;,
   3;6,6,6;,
   3;6,6,6;,
   3;6,6,6;,
   3;6,6,6;,
   3;35,7,35;,
   3;7,35,7;,
   3;35,7,35;,
   3;7,35,8;,
   3;9,9,9;,
   3;9,9,9;,
   3;9,9,9;,
   3;9,9,9;;
  }

  MeshMaterialList  {
   1;
   86;
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0;
   { Material__84 }
  }

  MeshTextureCoords  {
   124;
   0.171269;0.649934;,
   0.002000;0.649934;,
   0.171269;0.480666;,
   0.002000;0.480666;,
   0.171269;0.306633;,
   0.002000;0.306633;,
   0.171269;0.475901;,
   0.002000;0.475901;,
   0.481819;0.931373;,
   0.465174;0.931373;,
   0.465174;0.991182;,
   0.481819;0.991182;,
   0.452989;0.931373;,
   0.452989;0.991182;,
   0.435154;0.931373;,
   0.435154;0.991182;,
   0.418509;0.931373;,
   0.418509;0.991182;,
   0.564087;0.865750;,
   0.564087;0.925559;,
   0.547442;0.865750;,
   0.547442;0.925559;,
   0.530797;0.865750;,
   0.530797;0.925559;,
   0.518612;0.865750;,
   0.518612;0.925559;,
   0.494004;0.870373;,
   0.494004;0.930182;,
   0.477359;0.870373;,
   0.477359;0.930182;,
   0.498464;0.931373;,
   0.498464;0.991182;,
   0.002053;0.277942;,
   0.002000;0.287917;,
   0.006942;0.296582;,
   0.015554;0.301616;,
   0.025529;0.301668;,
   0.034194;0.296727;,
   0.039227;0.288115;,
   0.039280;0.278140;,
   0.034338;0.269475;,
   0.025726;0.264442;,
   0.015751;0.264389;,
   0.007086;0.269330;,
   0.597962;0.653217;,
   0.998000;0.653217;,
   0.998000;0.483949;,
   0.597962;0.483949;,
   0.597962;0.825609;,
   0.998000;0.825609;,
   0.597962;0.480826;,
   0.998000;0.480826;,
   0.597962;0.656340;,
   0.998000;0.656340;,
   0.597962;0.311557;,
   0.998000;0.311557;,
   0.998000;0.998000;,
   0.597962;0.828731;,
   0.998000;0.828731;,
   0.597962;0.998000;,
   0.451798;0.991182;,
   0.451798;0.931373;,
   0.576271;0.925559;,
   0.576271;0.865750;,
   0.510648;0.930182;,
   0.510648;0.870373;,
   0.510648;0.991182;,
   0.510648;0.931373;,
   0.511963;0.967811;,
   0.530527;0.972689;,
   0.520685;0.982673;,
   0.525478;0.964086;,
   0.539201;0.977615;,
   0.535670;0.991182;,
   0.549176;0.977543;,
   0.552901;0.991058;,
   0.557779;0.972494;,
   0.567762;0.982336;,
   0.562704;0.963820;,
   0.576271;0.967351;,
   0.562633;0.953845;,
   0.576148;0.950120;,
   0.557584;0.945242;,
   0.567426;0.935259;,
   0.548910;0.940317;,
   0.552441;0.926750;,
   0.538935;0.940388;,
   0.535210;0.926873;,
   0.530332;0.945437;,
   0.520348;0.935595;,
   0.525407;0.954111;,
   0.511839;0.950580;,
   0.176033;0.654698;,
   0.184496;0.823967;,
   0.176033;0.823967;,
   0.184496;0.654698;,
   0.592998;0.823967;,
   0.584534;0.654698;,
   0.592998;0.654698;,
   0.584534;0.823967;,
   0.176033;0.480666;,
   0.184496;0.649934;,
   0.176033;0.649934;,
   0.184496;0.480666;,
   0.592998;0.649934;,
   0.584534;0.480666;,
   0.592998;0.480666;,
   0.584534;0.649934;,
   0.176033;0.828731;,
   0.184496;0.998000;,
   0.176033;0.998000;,
   0.184496;0.828731;,
   0.592998;0.998000;,
   0.584534;0.828731;,
   0.592998;0.828731;,
   0.584534;0.998000;,
   0.176033;0.306633;,
   0.184496;0.475901;,
   0.176033;0.475901;,
   0.184496;0.306633;,
   0.592998;0.475901;,
   0.584534;0.306633;,
   0.592998;0.306633;,
   0.584534;0.475901;;
  }
 }
}

AnimationSet Anim-1 {
 

 Animation Anim-yinjing30 {
  
  { yinjing30 }

  AnimationKey {
   4;
   101;
   0;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-0.850000,-0.000000,1.000000;;,
   160;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-0.850000,-0.000000,1.000000;;,
   320;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-0.850000,-0.000000,1.000000;;,
   480;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-0.850000,-0.000000,1.000000;;,
   640;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-0.850000,-0.000000,1.000000;;,
   800;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-0.850000,-0.000000,1.000000;;,
   960;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-0.850000,-0.000000,1.000000;;,
   1120;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-0.850000,-0.000000,1.000000;;,
   1280;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-0.850000,-0.000000,1.000000;;,
   1440;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-0.850000,-0.000000,1.000000;;,
   1600;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-0.850000,-0.000000,1.000000;;,
   1760;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-0.850000,-0.000000,1.000000;;,
   1920;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-0.850000,-0.000000,1.000000;;,
   2080;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-0.850000,-0.000000,1.000000;;,
   2240;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-0.850000,-0.000000,1.000000;;,
   2400;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-0.850000,-0.000000,1.000000;;,
   2560;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-0.850000,-0.000000,1.000000;;,
   2720;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-0.850000,-0.000000,1.000000;;,
   2880;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-0.850000,-0.000000,1.000000;;,
   3040;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-0.850000,-0.000000,1.000000;;,
   3200;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-0.850000,-0.000000,1.000000;;,
   3360;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-0.850000,-0.000000,1.000000;;,
   3520;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-0.850000,-0.000000,1.000000;;,
   3680;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-0.850000,-0.000000,1.000000;;,
   3840;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-0.850000,-0.000000,1.000000;;,
   4000;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-0.850000,-0.000000,1.000000;;,
   4160;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-0.850000,-0.000000,1.000000;;,
   4320;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-0.850000,-0.000000,1.000000;;,
   4480;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-0.850000,-0.000000,1.000000;;,
   4640;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-0.850000,-0.000000,1.000000;;,
   4800;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-0.850000,-0.000000,1.000000;;,
   4960;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-0.850000,-0.000000,1.000000;;,
   5120;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-0.850000,-0.000000,1.000000;;,
   5280;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-0.850000,-0.000000,1.000000;;,
   5440;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-0.850000,-0.000000,1.000000;;,
   5600;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-0.850000,-0.000000,1.000000;;,
   5760;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-0.850000,-0.000000,1.000000;;,
   5920;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-0.850000,-0.000000,1.000000;;,
   6080;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-0.850000,-0.000000,1.000000;;,
   6240;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-0.850000,-0.000000,1.000000;;,
   6400;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-0.850000,-0.000000,1.000000;;,
   6560;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-0.850000,-0.000000,1.000000;;,
   6720;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-0.850000,-0.000000,1.000000;;,
   6880;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-0.850000,-0.000000,1.000000;;,
   7040;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-0.850000,-0.000000,1.000000;;,
   7200;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-0.850000,-0.000000,1.000000;;,
   7360;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-0.850000,-0.000000,1.000000;;,
   7520;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-0.850000,-0.000000,1.000000;;,
   7680;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-0.850000,-0.000000,1.000000;;,
   7840;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-0.850000,-0.000000,1.000000;;,
   8000;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-0.850000,-0.000000,1.000000;;,
   8160;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-0.850000,-0.000000,1.000000;;,
   8320;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-0.850000,-0.000000,1.000000;;,
   8480;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-0.850000,-0.000000,1.000000;;,
   8640;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-0.850000,-0.000000,1.000000;;,
   8800;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-0.850000,-0.000000,1.000000;;,
   8960;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-0.850000,-0.000000,1.000000;;,
   9120;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-0.850000,-0.000000,1.000000;;,
   9280;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-0.850000,-0.000000,1.000000;;,
   9440;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-0.850000,-0.000000,1.000000;;,
   9600;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-0.850000,-0.000000,1.000000;;,
   9760;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-0.850000,-0.000000,1.000000;;,
   9920;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-0.850000,-0.000000,1.000000;;,
   10080;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-0.850000,-0.000000,1.000000;;,
   10240;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-0.850000,-0.000000,1.000000;;,
   10400;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-0.850000,-0.000000,1.000000;;,
   10560;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-0.850000,-0.000000,1.000000;;,
   10720;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-0.850000,-0.000000,1.000000;;,
   10880;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-0.850000,-0.000000,1.000000;;,
   11040;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-0.850000,-0.000000,1.000000;;,
   11200;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-0.850000,-0.000000,1.000000;;,
   11360;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-0.850000,-0.000000,1.000000;;,
   11520;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-0.850000,-0.000000,1.000000;;,
   11680;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-0.850000,-0.000000,1.000000;;,
   11840;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-0.850000,-0.000000,1.000000;;,
   12000;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-0.850000,-0.000000,1.000000;;,
   12160;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-0.850000,-0.000000,1.000000;;,
   12320;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-0.850000,-0.000000,1.000000;;,
   12480;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-0.850000,-0.000000,1.000000;;,
   12640;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-0.850000,-0.000000,1.000000;;,
   12800;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-0.850000,-0.000000,1.000000;;,
   12960;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-0.850000,-0.000000,1.000000;;,
   13120;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-0.850000,-0.000000,1.000000;;,
   13280;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-0.850000,-0.000000,1.000000;;,
   13440;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-0.850000,-0.000000,1.000000;;,
   13600;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-0.850000,-0.000000,1.000000;;,
   13760;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-0.850000,-0.000000,1.000000;;,
   13920;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-0.850000,-0.000000,1.000000;;,
   14080;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-0.850000,-0.000000,1.000000;;,
   14240;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-0.850000,-0.000000,1.000000;;,
   14400;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-0.850000,-0.000000,1.000000;;,
   14560;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-0.850000,-0.000000,1.000000;;,
   14720;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-0.850000,-0.000000,1.000000;;,
   14880;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-0.850000,-0.000000,1.000000;;,
   15040;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-0.850000,-0.000000,1.000000;;,
   15200;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-0.850000,-0.000000,1.000000;;,
   15360;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-0.850000,-0.000000,1.000000;;,
   15520;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-0.850000,-0.000000,1.000000;;,
   15680;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-0.850000,-0.000000,1.000000;;,
   15840;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-0.850000,-0.000000,1.000000;;,
   16000;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-0.850000,-0.000000,1.000000;;;
  }
 }
}