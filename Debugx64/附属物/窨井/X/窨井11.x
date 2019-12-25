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
  "yinjing11.jpg";
 }
}

Frame yinjing11 {
 

 FrameTransformMatrix {
  1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-1.150000,-0.000000,1.000000;;
 }

 Mesh  {
  124;
  -1.500000;0.000000;-1.500000;,
  1.500000;0.000000;-1.500000;,
  -1.500000;0.000000;1.500000;,
  1.500000;0.000000;1.500000;,
  -1.500000;3.407622;-1.500000;,
  1.500000;3.407622;-1.500000;,
  -1.500000;3.407622;1.500000;,
  1.500000;3.407622;1.500000;,
  -0.186489;3.407622;-0.792922;,
  -0.265534;3.407622;-0.497922;,
  -0.265534;3.807621;-0.497922;,
  -0.186489;3.807622;-0.792922;,
  -0.481489;3.407622;-0.281967;,
  -0.481489;3.807621;-0.281967;,
  -0.776489;3.407622;-0.202922;,
  -0.776489;3.807621;-0.202922;,
  -1.071489;3.407622;-0.281967;,
  -1.071489;3.807621;-0.281967;,
  -1.287444;3.407622;-0.497922;,
  -1.287444;3.807621;-0.497922;,
  -1.366489;3.407622;-0.792922;,
  -1.366489;3.807622;-0.792922;,
  -1.287444;3.407622;-1.087922;,
  -1.287444;3.807622;-1.087922;,
  -1.071489;3.407622;-1.303877;,
  -1.071489;3.807622;-1.303877;,
  -0.776489;3.407622;-1.382922;,
  -0.776489;3.807622;-1.382922;,
  -0.481489;3.407622;-1.303877;,
  -0.481489;3.807622;-1.303877;,
  -0.265534;3.407622;-1.087922;,
  -0.265534;3.807622;-1.087923;,
  -0.434955;3.807622;-0.792922;,
  -0.480712;3.807621;-0.622155;,
  -0.605722;3.807621;-0.497145;,
  -0.776489;3.807621;-0.451388;,
  -0.947256;3.807621;-0.497145;,
  -1.072266;3.807621;-0.622155;,
  -1.118022;3.807622;-0.792922;,
  -1.072266;3.807622;-0.963689;,
  -0.947256;3.807622;-1.088699;,
  -0.776489;3.807622;-1.134456;,
  -0.605722;3.807622;-1.088699;,
  -0.480712;3.807622;-0.963689;,
  1.500000;0.150000;-1.500000;,
  1.500000;3.257622;-1.500000;,
  -1.500000;3.257622;-1.500000;,
  -1.500000;0.150000;-1.500000;,
  1.500000;0.150000;1.500000;,
  1.500000;3.257622;1.500000;,
  -1.500000;0.150000;1.500000;,
  -1.500000;3.257622;1.500000;,
  1.500000;0.150000;-1.500000;,
  1.500000;3.257622;-1.500000;,
  1.500000;0.150000;1.500000;,
  1.500000;3.257622;1.500000;,
  -1.500000;3.257622;-1.500000;,
  -1.500000;0.150000;1.500000;,
  -1.500000;3.257622;1.500000;,
  -1.500000;0.150000;-1.500000;,
  -0.481489;3.807621;-0.281967;,
  -0.481489;3.407622;-0.281967;,
  -1.071489;3.807621;-0.281967;,
  -1.071489;3.407622;-0.281967;,
  -1.071489;3.807622;-1.303877;,
  -1.071489;3.407622;-1.303877;,
  -0.481489;3.807622;-1.303877;,
  -0.481489;3.407622;-1.303877;,
  -0.186489;3.807622;-0.792922;,
  -0.480712;3.807621;-0.622155;,
  -0.265534;3.807621;-0.497922;,
  -0.434955;3.807622;-0.792922;,
  -0.605722;3.807621;-0.497145;,
  -0.481489;3.807621;-0.281967;,
  -0.776489;3.807621;-0.451388;,
  -0.776489;3.807621;-0.202922;,
  -0.947256;3.807621;-0.497145;,
  -1.071489;3.807621;-0.281967;,
  -1.072266;3.807621;-0.622155;,
  -1.287444;3.807621;-0.497922;,
  -1.118022;3.807622;-0.792922;,
  -1.366489;3.807622;-0.792922;,
  -1.072266;3.807622;-0.963689;,
  -1.287444;3.807622;-1.087922;,
  -0.947256;3.807622;-1.088699;,
  -1.071489;3.807622;-1.303877;,
  -0.776489;3.807622;-1.134456;,
  -0.776489;3.807622;-1.382922;,
  -0.605722;3.807622;-1.088699;,
  -0.481489;3.807622;-1.303877;,
  -0.480712;3.807622;-0.963689;,
  -0.265534;3.807622;-1.087923;,
  1.500000;3.407622;-1.500000;,
  -1.500000;3.257622;-1.500000;,
  -1.500000;3.407622;-1.500000;,
  1.500000;3.257622;-1.500000;,
  -1.500000;0.000000;-1.500000;,
  1.500000;0.150000;-1.500000;,
  1.500000;0.000000;-1.500000;,
  -1.500000;0.150000;-1.500000;,
  1.500000;3.407622;1.500000;,
  1.500000;3.257622;-1.500000;,
  1.500000;3.407622;-1.500000;,
  1.500000;3.257622;1.500000;,
  1.500000;0.000000;-1.500000;,
  1.500000;0.150000;1.500000;,
  1.500000;0.000000;1.500000;,
  1.500000;0.150000;-1.500000;,
  -1.500000;3.407622;1.500000;,
  1.500000;3.257622;1.500000;,
  1.500000;3.407622;1.500000;,
  -1.500000;3.257622;1.500000;,
  1.500000;0.000000;1.500000;,
  -1.500000;0.150000;1.500000;,
  -1.500000;0.000000;1.500000;,
  1.500000;0.150000;1.500000;,
  -1.500000;3.407622;-1.500000;,
  -1.500000;3.257622;1.500000;,
  -1.500000;3.407622;1.500000;,
  -1.500000;3.257622;-1.500000;,
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
   45;
   0.000000;-1.000000;0.000000;,
   0.000000;1.000000;0.000000;,
   0.000000;0.000000;-1.000000;,
   1.000000;0.000000;0.000000;,
   0.000000;0.000000;1.000000;,
   -1.000000;0.000000;0.000000;,
   1.000000;-0.000000;-0.000001;,
   0.866025;-0.000000;0.500000;,
   0.866025;-0.000000;0.500000;,
   1.000000;0.000000;-0.000001;,
   0.500000;-0.000000;0.866026;,
   0.500000;-0.000000;0.866026;,
   0.000000;-0.000001;1.000000;,
   0.000000;-0.000001;1.000000;,
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
   0.000000;1.000000;0.000001;,
   0.000000;1.000000;0.000000;,
   -0.000000;1.000000;0.000001;,
   0.000000;1.000000;0.000000;,
   0.000003;1.000000;0.000001;,
   -0.000000;1.000000;0.000000;,
   -0.000003;1.000000;0.000001;,
   -0.000000;1.000000;0.000000;,
   -0.000000;1.000000;0.000000;,
   -0.000000;1.000000;0.000000;,
   0.000000;1.000000;0.000001;,
   0.000000;1.000000;0.000001;,
   0.000000;1.000000;0.000000;,
   0.000000;1.000000;0.000000;,
   0.000000;1.000000;0.000000;;
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
   3;30,31,1;,
   3;31,32,1;,
   3;32,33,34;,
   3;31,33,32;,
   3;33,1,1;,
   3;1,35,1;,
   3;33,35,1;,
   3;31,35,33;,
   3;30,35,31;,
   3;36,35,30;,
   3;37,38,39;,
   3;38,37,40;,
   3;39,1,1;,
   3;1,39,38;,
   3;1,1,1;,
   3;1,1,1;,
   3;1,1,1;,
   3;1,1,1;,
   3;1,41,42;,
   3;41,1,1;,
   3;42,43,44;,
   3;43,42,41;,
   3;44,1,1;,
   3;1,44,43;,
   3;1,1,1;,
   3;1,1,1;,
   3;1,1,1;,
   3;1,1,1;,
   3;1,1,1;,
   3;1,1,1;,
   3;1,1,1;,
   3;1,1,1;,
   3;1,40,37;,
   3;40,1,1;,
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
   0.232571;0.966671;,
   0.002000;0.966671;,
   0.232571;0.736100;,
   0.002000;0.736100;,
   0.232571;0.470584;,
   0.002000;0.470584;,
   0.232571;0.701155;,
   0.002000;0.701155;,
   0.280837;0.853971;,
   0.280837;0.831298;,
   0.250094;0.831298;,
   0.250094;0.853971;,
   0.280837;0.814700;,
   0.250094;0.814700;,
   0.312785;0.870569;,
   0.282042;0.870569;,
   0.312785;0.847896;,
   0.282042;0.847896;,
   0.369809;0.965616;,
   0.339066;0.965616;,
   0.369809;0.942943;,
   0.339066;0.942943;,
   0.369809;0.920270;,
   0.339066;0.920270;,
   0.369809;0.903673;,
   0.339066;0.903673;,
   0.401757;0.959541;,
   0.371014;0.959541;,
   0.401757;0.936868;,
   0.371014;0.936868;,
   0.280837;0.876644;,
   0.250094;0.876644;,
   0.724034;0.997928;,
   0.737621;0.998000;,
   0.749424;0.991269;,
   0.756280;0.979538;,
   0.756352;0.965950;,
   0.749621;0.954147;,
   0.737890;0.947291;,
   0.724302;0.947219;,
   0.712499;0.953950;,
   0.705643;0.965681;,
   0.705571;0.979269;,
   0.712302;0.991072;,
   0.240843;0.235388;,
   0.002000;0.235388;,
   0.002000;0.465959;,
   0.240843;0.465959;,
   0.482502;0.235388;,
   0.243659;0.235388;,
   0.482502;0.002000;,
   0.243659;0.002000;,
   0.482502;0.465959;,
   0.243659;0.465959;,
   0.482502;0.232571;,
   0.243659;0.232571;,
   0.002000;0.002000;,
   0.240843;0.232571;,
   0.002000;0.232571;,
   0.240843;0.002000;,
   0.282042;0.893242;,
   0.312785;0.893242;,
   0.339066;0.982214;,
   0.369809;0.982214;,
   0.371014;0.982214;,
   0.401757;0.982214;,
   0.250094;0.893242;,
   0.280837;0.893242;,
   0.281928;0.894615;,
   0.275284;0.919902;,
   0.261685;0.906496;,
   0.287002;0.913025;,
   0.268575;0.931718;,
   0.250094;0.926907;,
   0.268672;0.945305;,
   0.250262;0.950380;,
   0.275550;0.957024;,
   0.262143;0.970623;,
   0.287365;0.963733;,
   0.282555;0.982214;,
   0.300952;0.963636;,
   0.306027;0.982046;,
   0.312671;0.956758;,
   0.326270;0.970164;,
   0.319380;0.944943;,
   0.337861;0.949753;,
   0.319283;0.931355;,
   0.337693;0.926281;,
   0.312405;0.919637;,
   0.325812;0.906038;,
   0.300590;0.912927;,
   0.305400;0.894447;,
   0.466759;0.470584;,
   0.236187;0.482112;,
   0.236187;0.470584;,
   0.466759;0.482112;,
   0.236187;0.732484;,
   0.466759;0.720955;,
   0.466759;0.732484;,
   0.236187;0.720955;,
   0.466759;0.736100;,
   0.236187;0.747628;,
   0.236187;0.736100;,
   0.466759;0.747628;,
   0.236187;0.998000;,
   0.466759;0.986471;,
   0.466759;0.998000;,
   0.236187;0.986471;,
   0.700946;0.736100;,
   0.470375;0.747628;,
   0.470375;0.736100;,
   0.700946;0.747628;,
   0.470375;0.998000;,
   0.700946;0.986471;,
   0.700946;0.998000;,
   0.470375;0.986471;,
   0.700946;0.470584;,
   0.470375;0.482112;,
   0.470375;0.470584;,
   0.700946;0.482112;,
   0.470375;0.732484;,
   0.700946;0.720955;,
   0.700946;0.732484;,
   0.470375;0.720955;;
  }
 }
}

AnimationSet Anim-1 {
 

 Animation Anim-yinjing11 {
  
  { yinjing11 }

  AnimationKey {
   4;
   101;
   0;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-1.150000,-0.000000,1.000000;;,
   160;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-1.150000,-0.000000,1.000000;;,
   320;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-1.150000,-0.000000,1.000000;;,
   480;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-1.150000,-0.000000,1.000000;;,
   640;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-1.150000,-0.000000,1.000000;;,
   800;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-1.150000,-0.000000,1.000000;;,
   960;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-1.150000,-0.000000,1.000000;;,
   1120;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-1.150000,-0.000000,1.000000;;,
   1280;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-1.150000,-0.000000,1.000000;;,
   1440;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-1.150000,-0.000000,1.000000;;,
   1600;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-1.150000,-0.000000,1.000000;;,
   1760;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-1.150000,-0.000000,1.000000;;,
   1920;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-1.150000,-0.000000,1.000000;;,
   2080;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-1.150000,-0.000000,1.000000;;,
   2240;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-1.150000,-0.000000,1.000000;;,
   2400;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-1.150000,-0.000000,1.000000;;,
   2560;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-1.150000,-0.000000,1.000000;;,
   2720;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-1.150000,-0.000000,1.000000;;,
   2880;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-1.150000,-0.000000,1.000000;;,
   3040;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-1.150000,-0.000000,1.000000;;,
   3200;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-1.150000,-0.000000,1.000000;;,
   3360;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-1.150000,-0.000000,1.000000;;,
   3520;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-1.150000,-0.000000,1.000000;;,
   3680;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-1.150000,-0.000000,1.000000;;,
   3840;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-1.150000,-0.000000,1.000000;;,
   4000;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-1.150000,-0.000000,1.000000;;,
   4160;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-1.150000,-0.000000,1.000000;;,
   4320;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-1.150000,-0.000000,1.000000;;,
   4480;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-1.150000,-0.000000,1.000000;;,
   4640;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-1.150000,-0.000000,1.000000;;,
   4800;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-1.150000,-0.000000,1.000000;;,
   4960;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-1.150000,-0.000000,1.000000;;,
   5120;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-1.150000,-0.000000,1.000000;;,
   5280;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-1.150000,-0.000000,1.000000;;,
   5440;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-1.150000,-0.000000,1.000000;;,
   5600;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-1.150000,-0.000000,1.000000;;,
   5760;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-1.150000,-0.000000,1.000000;;,
   5920;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-1.150000,-0.000000,1.000000;;,
   6080;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-1.150000,-0.000000,1.000000;;,
   6240;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-1.150000,-0.000000,1.000000;;,
   6400;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-1.150000,-0.000000,1.000000;;,
   6560;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-1.150000,-0.000000,1.000000;;,
   6720;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-1.150000,-0.000000,1.000000;;,
   6880;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-1.150000,-0.000000,1.000000;;,
   7040;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-1.150000,-0.000000,1.000000;;,
   7200;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-1.150000,-0.000000,1.000000;;,
   7360;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-1.150000,-0.000000,1.000000;;,
   7520;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-1.150000,-0.000000,1.000000;;,
   7680;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-1.150000,-0.000000,1.000000;;,
   7840;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-1.150000,-0.000000,1.000000;;,
   8000;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-1.150000,-0.000000,1.000000;;,
   8160;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-1.150000,-0.000000,1.000000;;,
   8320;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-1.150000,-0.000000,1.000000;;,
   8480;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-1.150000,-0.000000,1.000000;;,
   8640;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-1.150000,-0.000000,1.000000;;,
   8800;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-1.150000,-0.000000,1.000000;;,
   8960;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-1.150000,-0.000000,1.000000;;,
   9120;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-1.150000,-0.000000,1.000000;;,
   9280;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-1.150000,-0.000000,1.000000;;,
   9440;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-1.150000,-0.000000,1.000000;;,
   9600;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-1.150000,-0.000000,1.000000;;,
   9760;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-1.150000,-0.000000,1.000000;;,
   9920;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-1.150000,-0.000000,1.000000;;,
   10080;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-1.150000,-0.000000,1.000000;;,
   10240;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-1.150000,-0.000000,1.000000;;,
   10400;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-1.150000,-0.000000,1.000000;;,
   10560;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-1.150000,-0.000000,1.000000;;,
   10720;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-1.150000,-0.000000,1.000000;;,
   10880;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-1.150000,-0.000000,1.000000;;,
   11040;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-1.150000,-0.000000,1.000000;;,
   11200;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-1.150000,-0.000000,1.000000;;,
   11360;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-1.150000,-0.000000,1.000000;;,
   11520;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-1.150000,-0.000000,1.000000;;,
   11680;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-1.150000,-0.000000,1.000000;;,
   11840;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-1.150000,-0.000000,1.000000;;,
   12000;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-1.150000,-0.000000,1.000000;;,
   12160;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-1.150000,-0.000000,1.000000;;,
   12320;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-1.150000,-0.000000,1.000000;;,
   12480;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-1.150000,-0.000000,1.000000;;,
   12640;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-1.150000,-0.000000,1.000000;;,
   12800;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-1.150000,-0.000000,1.000000;;,
   12960;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-1.150000,-0.000000,1.000000;;,
   13120;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-1.150000,-0.000000,1.000000;;,
   13280;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-1.150000,-0.000000,1.000000;;,
   13440;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-1.150000,-0.000000,1.000000;;,
   13600;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-1.150000,-0.000000,1.000000;;,
   13760;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-1.150000,-0.000000,1.000000;;,
   13920;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-1.150000,-0.000000,1.000000;;,
   14080;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-1.150000,-0.000000,1.000000;;,
   14240;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-1.150000,-0.000000,1.000000;;,
   14400;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-1.150000,-0.000000,1.000000;;,
   14560;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-1.150000,-0.000000,1.000000;;,
   14720;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-1.150000,-0.000000,1.000000;;,
   14880;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-1.150000,-0.000000,1.000000;;,
   15040;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-1.150000,-0.000000,1.000000;;,
   15200;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-1.150000,-0.000000,1.000000;;,
   15360;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-1.150000,-0.000000,1.000000;;,
   15520;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-1.150000,-0.000000,1.000000;;,
   15680;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-1.150000,-0.000000,1.000000;;,
   15840;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-1.150000,-0.000000,1.000000;;,
   16000;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-1.150000,-0.000000,1.000000;;;
  }
 }
}