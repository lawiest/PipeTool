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
  "yinjing07.jpg";
 }
}

Frame yinjing07 {
 

 FrameTransformMatrix {
  1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-0.850000,-0.000000,1.000000;;
 }

 Mesh  {
  124;
  -1.500000;0.000000;-1.500000;,
  1.500000;0.000000;-1.500000;,
  -1.500000;0.000000;1.500000;,
  1.500000;0.000000;1.500000;,
  -1.500000;2.950000;-1.500000;,
  1.500000;2.950000;-1.500000;,
  -1.500000;2.950000;1.500000;,
  1.500000;2.950000;1.500000;,
  -0.186489;2.950000;-0.792922;,
  -0.265534;2.950000;-0.497922;,
  -0.265534;3.350000;-0.497922;,
  -0.186489;3.350000;-0.792922;,
  -0.481489;2.950000;-0.281967;,
  -0.481489;3.350000;-0.281967;,
  -0.776489;2.950000;-0.202922;,
  -0.776489;3.350000;-0.202922;,
  -1.071489;2.950000;-0.281967;,
  -1.071489;3.350000;-0.281967;,
  -1.287444;2.950000;-0.497922;,
  -1.287444;3.350000;-0.497922;,
  -1.366489;2.950000;-0.792922;,
  -1.366489;3.350000;-0.792922;,
  -1.287444;2.950000;-1.087922;,
  -1.287444;3.350000;-1.087922;,
  -1.071489;2.950000;-1.303877;,
  -1.071489;3.350000;-1.303877;,
  -0.776489;2.950000;-1.382922;,
  -0.776489;3.350000;-1.382922;,
  -0.481489;2.950000;-1.303877;,
  -0.481489;3.350000;-1.303877;,
  -0.265534;2.950000;-1.087922;,
  -0.265534;3.350000;-1.087923;,
  -0.434955;3.350000;-0.792922;,
  -0.480712;3.350000;-0.622155;,
  -0.605722;3.350000;-0.497145;,
  -0.776489;3.350000;-0.451388;,
  -0.947256;3.350000;-0.497145;,
  -1.072266;3.350000;-0.622155;,
  -1.118022;3.350000;-0.792922;,
  -1.072266;3.350000;-0.963689;,
  -0.947256;3.350000;-1.088699;,
  -0.776489;3.350000;-1.134456;,
  -0.605722;3.350000;-1.088699;,
  -0.480712;3.350000;-0.963689;,
  1.500000;0.150000;-1.500000;,
  1.500000;2.800000;-1.500000;,
  -1.500000;2.800000;-1.500000;,
  -1.500000;0.150000;-1.500000;,
  1.500000;0.150000;1.500000;,
  1.500000;2.800000;1.500000;,
  -1.500000;0.150000;1.500000;,
  -1.500000;2.800000;1.500000;,
  1.500000;0.150000;-1.500000;,
  1.500000;2.800000;-1.500000;,
  1.500000;0.150000;1.500000;,
  1.500000;2.800000;1.500000;,
  -1.500000;2.800000;-1.500000;,
  -1.500000;0.150000;1.500000;,
  -1.500000;2.800000;1.500000;,
  -1.500000;0.150000;-1.500000;,
  -0.481489;3.350000;-0.281967;,
  -0.481489;2.950000;-0.281967;,
  -1.071489;3.350000;-0.281967;,
  -1.071489;2.950000;-0.281967;,
  -1.071489;3.350000;-1.303877;,
  -1.071489;2.950000;-1.303877;,
  -0.481489;3.350000;-1.303877;,
  -0.481489;2.950000;-1.303877;,
  -0.186489;3.350000;-0.792922;,
  -0.480712;3.350000;-0.622155;,
  -0.265534;3.350000;-0.497922;,
  -0.434955;3.350000;-0.792922;,
  -0.605722;3.350000;-0.497145;,
  -0.481489;3.350000;-0.281967;,
  -0.776489;3.350000;-0.451388;,
  -0.776489;3.350000;-0.202922;,
  -0.947256;3.350000;-0.497145;,
  -1.071489;3.350000;-0.281967;,
  -1.072266;3.350000;-0.622155;,
  -1.287444;3.350000;-0.497922;,
  -1.118022;3.350000;-0.792922;,
  -1.366489;3.350000;-0.792922;,
  -1.072266;3.350000;-0.963689;,
  -1.287444;3.350000;-1.087922;,
  -0.947256;3.350000;-1.088699;,
  -1.071489;3.350000;-1.303877;,
  -0.776489;3.350000;-1.134456;,
  -0.776489;3.350000;-1.382922;,
  -0.605722;3.350000;-1.088699;,
  -0.481489;3.350000;-1.303877;,
  -0.480712;3.350000;-0.963689;,
  -0.265534;3.350000;-1.087923;,
  1.500000;2.950000;-1.500000;,
  -1.500000;2.800000;-1.500000;,
  -1.500000;2.950000;-1.500000;,
  1.500000;2.800000;-1.500000;,
  -1.500000;0.000000;-1.500000;,
  1.500000;0.150000;-1.500000;,
  1.500000;0.000000;-1.500000;,
  -1.500000;0.150000;-1.500000;,
  1.500000;2.950000;1.500000;,
  1.500000;2.800000;-1.500000;,
  1.500000;2.950000;-1.500000;,
  1.500000;2.800000;1.500000;,
  1.500000;0.000000;-1.500000;,
  1.500000;0.150000;1.500000;,
  1.500000;0.000000;1.500000;,
  1.500000;0.150000;-1.500000;,
  -1.500000;2.950000;1.500000;,
  1.500000;2.800000;1.500000;,
  1.500000;2.950000;1.500000;,
  -1.500000;2.800000;1.500000;,
  1.500000;0.000000;1.500000;,
  -1.500000;0.150000;1.500000;,
  -1.500000;0.000000;1.500000;,
  1.500000;0.150000;1.500000;,
  -1.500000;2.950000;-1.500000;,
  -1.500000;2.800000;1.500000;,
  -1.500000;2.950000;1.500000;,
  -1.500000;2.800000;-1.500000;,
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
   35;
   0.000000;-1.000000;0.000000;,
   0.000000;1.000000;0.000000;,
   0.000000;0.000000;-1.000000;,
   1.000000;0.000000;0.000000;,
   0.000000;0.000000;1.000000;,
   -1.000000;0.000000;0.000000;,
   1.000000;-0.000000;-0.000001;,
   0.866025;-0.000000;0.500000;,
   0.866025;-0.000000;0.500000;,
   1.000000;0.000000;-0.000000;,
   0.500000;-0.000000;0.866026;,
   0.500000;-0.000000;0.866026;,
   0.000000;-0.000000;1.000000;,
   0.000000;-0.000000;1.000000;,
   -0.500000;-0.000000;0.866026;,
   -0.500000;-0.000000;0.866026;,
   -0.866025;-0.000000;0.500000;,
   -0.866025;-0.000000;0.500000;,
   -1.000000;0.000000;0.000000;,
   -1.000000;-0.000000;0.000000;,
   -0.866026;-0.000000;-0.500000;,
   -0.866025;-0.000000;-0.500000;,
   -0.500000;0.000000;-0.866025;,
   -0.500000;0.000000;-0.866025;,
   -0.000001;0.000000;-1.000000;,
   -0.000001;0.000000;-1.000000;,
   0.500000;0.000000;-0.866026;,
   0.500000;-0.000000;-0.866026;,
   0.866025;-0.000000;-0.500000;,
   0.866025;-0.000000;-0.500001;,
   -0.000000;1.000000;0.000001;,
   -0.000001;1.000000;0.000002;,
   -0.000000;1.000000;0.000002;,
   0.000000;1.000000;0.000001;,
   0.000001;1.000000;0.000000;;
   86;
   3;0,0,0;,
   3;0,0,0;,
   3;1,1,1;,
   3;1,1,1;,
   3;2,2,2;,
   3;2,2,2;,
   3;3,3,3;,
   3;3,3,3;,
   3;4,4,4;,
   3;4,4,4;,
   3;5,5,5;,
   3;5,5,5;,
   3;6,7,8;,
   3;7,6,9;,
   3;10,7,11;,
   3;7,10,8;,
   3;12,11,13;,
   3;11,12,10;,
   3;14,13,15;,
   3;13,14,12;,
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
   3;6,29,9;,
   3;29,6,28;,
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
   3;1,1,30;,
   3;1,1,1;,
   3;30,31,32;,
   3;31,30,1;,
   3;32,33,34;,
   3;33,32,31;,
   3;34,1,1;,
   3;1,34,33;,
   3;1,1,1;,
   3;1,1,1;,
   3;2,2,2;,
   3;2,2,2;,
   3;2,2,2;,
   3;2,2,2;,
   3;3,3,3;,
   3;3,3,3;,
   3;3,3,3;,
   3;3,3,3;,
   3;4,4,4;,
   3;4,4,4;,
   3;4,4,4;,
   3;4,4,4;,
   3;5,5,5;,
   3;5,5,5;,
   3;5,5,5;,
   3;5,5,5;;
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
   0.003309;0.998000;,
   0.003309;0.735657;,
   0.265652;0.998000;,
   0.265652;0.735657;,
   0.529303;0.998000;,
   0.529303;0.735657;,
   0.266960;0.998000;,
   0.266960;0.735657;,
   0.109739;0.278621;,
   0.109739;0.304418;,
   0.144718;0.304418;,
   0.144718;0.278621;,
   0.109739;0.323303;,
   0.144718;0.323303;,
   0.073451;0.259737;,
   0.108430;0.259737;,
   0.073451;0.285534;,
   0.108430;0.285534;,
   0.210908;0.353994;,
   0.245887;0.353994;,
   0.210908;0.379791;,
   0.245887;0.379791;,
   0.210908;0.405588;,
   0.245887;0.405588;,
   0.210908;0.424472;,
   0.245887;0.424472;,
   0.174620;0.360906;,
   0.209599;0.360906;,
   0.174620;0.386703;,
   0.209599;0.386703;,
   0.109739;0.252824;,
   0.144718;0.252824;,
   0.002082;0.175766;,
   0.002000;0.191226;,
   0.009659;0.204655;,
   0.023006;0.212456;,
   0.038466;0.212538;,
   0.051896;0.204879;,
   0.059696;0.191532;,
   0.059778;0.176072;,
   0.052120;0.162642;,
   0.038772;0.154842;,
   0.023312;0.154760;,
   0.009883;0.162418;,
   0.766264;0.998000;,
   0.998000;0.998000;,
   0.998000;0.735657;,
   0.766264;0.735657;,
   0.532555;0.998000;,
   0.764291;0.998000;,
   0.532555;0.733685;,
   0.764291;0.733685;,
   0.532555;0.735657;,
   0.764291;0.735657;,
   0.532555;0.471342;,
   0.764291;0.471342;,
   0.998000;0.733685;,
   0.766264;0.471342;,
   0.998000;0.471342;,
   0.766264;0.733685;,
   0.108430;0.233940;,
   0.073451;0.233940;,
   0.245887;0.335109;,
   0.210908;0.335109;,
   0.209599;0.335109;,
   0.174620;0.335109;,
   0.144718;0.233940;,
   0.109739;0.233940;,
   0.209667;0.333609;,
   0.217226;0.304837;,
   0.232699;0.320091;,
   0.203893;0.312662;,
   0.224860;0.291393;,
   0.245887;0.296867;,
   0.224750;0.275934;,
   0.245696;0.270160;,
   0.216924;0.262601;,
   0.232178;0.247127;,
   0.203480;0.254967;,
   0.208954;0.233940;,
   0.188021;0.255077;,
   0.182247;0.234131;,
   0.174688;0.262903;,
   0.159214;0.247649;,
   0.167054;0.276346;,
   0.146027;0.270873;,
   0.167164;0.291806;,
   0.146218;0.297579;,
   0.174990;0.305139;,
   0.159736;0.320612;,
   0.188433;0.312773;,
   0.182960;0.333800;,
   0.266960;0.734348;,
   0.529303;0.721231;,
   0.529303;0.734348;,
   0.266960;0.721231;,
   0.529303;0.476378;,
   0.266960;0.489495;,
   0.266960;0.476378;,
   0.529303;0.489495;,
   0.002000;0.473760;,
   0.264343;0.460643;,
   0.264343;0.473760;,
   0.002000;0.460643;,
   0.264343;0.215790;,
   0.002000;0.228907;,
   0.002000;0.215790;,
   0.264343;0.228907;,
   0.002000;0.734348;,
   0.264343;0.721231;,
   0.264343;0.734348;,
   0.002000;0.721231;,
   0.264343;0.476378;,
   0.002000;0.489495;,
   0.002000;0.476378;,
   0.264343;0.489495;,
   0.266960;0.473760;,
   0.529303;0.460643;,
   0.529303;0.473760;,
   0.266960;0.460643;,
   0.529303;0.215790;,
   0.266960;0.228907;,
   0.266960;0.215790;,
   0.529303;0.228907;;
  }
 }
}

AnimationSet Anim-1 {
 

 Animation Anim-yinjing07 {
  
  { yinjing07 }

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