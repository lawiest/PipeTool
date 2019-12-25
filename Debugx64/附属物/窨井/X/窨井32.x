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
  "yinjing32.jpg";
 }
}

Frame yinjing32 {
 

 FrameTransformMatrix {
  1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-0.850000,-0.000000,1.000000;;
 }

 Mesh  {
  124;
  -1.500000;0.000000;-1.500000;,
  1.500000;0.000000;-1.500000;,
  -1.500000;0.000000;1.500000;,
  1.500000;0.000000;1.500000;,
  -1.500000;11.289995;-1.500000;,
  1.500000;11.289995;-1.500000;,
  -1.500000;11.289995;1.500000;,
  1.500000;11.289995;1.500000;,
  -0.186489;11.289995;-0.792922;,
  -0.265534;11.289995;-0.497922;,
  -0.265534;12.350000;-0.497922;,
  -0.186489;12.350000;-0.792922;,
  -0.481489;11.289995;-0.281968;,
  -0.481489;12.350000;-0.281967;,
  -0.776489;11.289995;-0.202923;,
  -0.776489;12.350000;-0.202922;,
  -1.071489;11.289995;-0.281968;,
  -1.071489;12.350000;-0.281967;,
  -1.287444;11.289995;-0.497922;,
  -1.287444;12.350000;-0.497922;,
  -1.366489;11.289995;-0.792922;,
  -1.366489;12.350000;-0.792922;,
  -1.287444;11.289995;-1.087922;,
  -1.287444;12.350000;-1.087922;,
  -1.071489;11.289995;-1.303877;,
  -1.071489;12.350000;-1.303877;,
  -0.776489;11.289995;-1.382922;,
  -0.776489;12.350000;-1.382922;,
  -0.481489;11.289995;-1.303878;,
  -0.481489;12.350000;-1.303877;,
  -0.265534;11.289995;-1.087922;,
  -0.265534;12.350000;-1.087922;,
  -0.434955;12.350000;-0.792922;,
  -0.480712;12.350000;-0.622155;,
  -0.605722;12.350000;-0.497145;,
  -0.776489;12.350000;-0.451389;,
  -0.947256;12.350000;-0.497145;,
  -1.072266;12.350000;-0.622155;,
  -1.118022;12.350000;-0.792922;,
  -1.072266;12.350000;-0.963689;,
  -0.947256;12.350000;-1.088699;,
  -0.776489;12.350000;-1.134456;,
  -0.605722;12.350000;-1.088699;,
  -0.480712;12.350000;-0.963689;,
  1.500000;0.150000;-1.500000;,
  1.500000;11.139996;-1.500000;,
  -1.500000;11.139996;-1.500000;,
  -1.500000;0.150000;-1.500000;,
  1.500000;0.150000;1.500000;,
  1.500000;11.139996;1.500000;,
  -1.500000;0.150000;1.500000;,
  -1.500000;11.139996;1.500000;,
  1.500000;0.150000;-1.500000;,
  1.500000;11.139996;-1.500000;,
  1.500000;0.150000;1.500000;,
  1.500000;11.139996;1.500000;,
  -1.500000;11.139996;-1.500000;,
  -1.500000;0.150000;1.500000;,
  -1.500000;11.139996;1.500000;,
  -1.500000;0.150000;-1.500000;,
  -0.481489;12.350000;-0.281967;,
  -0.481489;11.289995;-0.281968;,
  -1.071489;12.350000;-0.281967;,
  -1.071489;11.289995;-0.281968;,
  -1.071489;12.350000;-1.303877;,
  -1.071489;11.289995;-1.303877;,
  -0.481489;12.350000;-1.303877;,
  -0.481489;11.289995;-1.303878;,
  -0.186489;12.350000;-0.792922;,
  -0.480712;12.350000;-0.622155;,
  -0.265534;12.350000;-0.497922;,
  -0.434955;12.350000;-0.792922;,
  -0.605722;12.350000;-0.497145;,
  -0.481489;12.350000;-0.281967;,
  -0.776489;12.350000;-0.451389;,
  -0.776489;12.350000;-0.202922;,
  -0.947256;12.350000;-0.497145;,
  -1.071489;12.350000;-0.281967;,
  -1.072266;12.350000;-0.622155;,
  -1.287444;12.350000;-0.497922;,
  -1.118022;12.350000;-0.792922;,
  -1.366489;12.350000;-0.792922;,
  -1.072266;12.350000;-0.963689;,
  -1.287444;12.350000;-1.087922;,
  -0.947256;12.350000;-1.088699;,
  -1.071489;12.350000;-1.303877;,
  -0.776489;12.350000;-1.134456;,
  -0.776489;12.350000;-1.382922;,
  -0.605722;12.350000;-1.088699;,
  -0.481489;12.350000;-1.303877;,
  -0.480712;12.350000;-0.963689;,
  -0.265534;12.350000;-1.087922;,
  1.500000;11.289995;-1.500000;,
  -1.500000;11.139996;-1.500000;,
  -1.500000;11.289995;-1.500000;,
  1.500000;11.139996;-1.500000;,
  -1.500000;0.000000;-1.500000;,
  1.500000;0.150000;-1.500000;,
  1.500000;0.000000;-1.500000;,
  -1.500000;0.150000;-1.500000;,
  1.500000;11.289995;1.500000;,
  1.500000;11.139996;-1.500000;,
  1.500000;11.289995;-1.500000;,
  1.500000;11.139996;1.500000;,
  1.500000;0.000000;-1.500000;,
  1.500000;0.150000;1.500000;,
  1.500000;0.000000;1.500000;,
  1.500000;0.150000;-1.500000;,
  -1.500000;11.289995;1.500000;,
  1.500000;11.139996;1.500000;,
  1.500000;11.289995;1.500000;,
  -1.500000;11.139996;1.500000;,
  1.500000;0.000000;1.500000;,
  -1.500000;0.150000;1.500000;,
  -1.500000;0.000000;1.500000;,
  1.500000;0.150000;1.500000;,
  -1.500000;11.289995;-1.500000;,
  -1.500000;11.139996;1.500000;,
  -1.500000;11.289995;1.500000;,
  -1.500000;11.139996;-1.500000;,
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
   1.000000;0.000000;-0.000001;,
   0.866025;-0.000000;0.500000;,
   0.866025;-0.000000;0.500000;,
   1.000000;0.000000;-0.000001;,
   0.500000;-0.000000;0.866026;,
   0.500000;-0.000000;0.866026;,
   0.000000;-0.000000;1.000000;,
   0.000000;-0.000000;1.000000;,
   -0.500000;-0.000000;0.866026;,
   -0.500000;-0.000000;0.866025;,
   -0.866025;-0.000000;0.500000;,
   -0.866025;0.000000;0.500000;,
   -1.000000;0.000000;0.000000;,
   -1.000000;-0.000000;0.000000;,
   -0.866026;0.000000;-0.500000;,
   -0.866026;0.000000;-0.500000;,
   -0.500000;0.000000;-0.866025;,
   -0.500000;0.000000;-0.866025;,
   -0.000000;0.000000;-1.000000;,
   -0.000000;0.000000;-1.000000;,
   0.500000;0.000000;-0.866025;,
   0.500000;0.000000;-0.866025;,
   0.866025;0.000000;-0.500000;,
   0.866025;0.000000;-0.500001;,
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
   0.266373;0.512392;,
   0.266373;0.384495;,
   0.394270;0.512392;,
   0.394270;0.384495;,
   0.398560;0.512392;,
   0.526457;0.512392;,
   0.398560;0.384495;,
   0.526457;0.384495;,
   0.051060;0.911989;,
   0.051060;0.899412;,
   0.005869;0.899412;,
   0.005869;0.911989;,
   0.051060;0.890206;,
   0.005869;0.890206;,
   0.051060;0.876557;,
   0.005869;0.876557;,
   0.051060;0.863980;,
   0.005869;0.863980;,
   0.100816;0.974322;,
   0.055625;0.974322;,
   0.100816;0.961745;,
   0.055625;0.961745;,
   0.100816;0.949169;,
   0.055625;0.949169;,
   0.100816;0.939962;,
   0.055625;0.939962;,
   0.097322;0.921195;,
   0.052132;0.921195;,
   0.097322;0.908619;,
   0.052132;0.908619;,
   0.051060;0.924565;,
   0.005869;0.924565;,
   0.012241;0.381441;,
   0.019778;0.381481;,
   0.026325;0.377747;,
   0.030128;0.371240;,
   0.030168;0.363703;,
   0.026434;0.357156;,
   0.019927;0.353353;,
   0.012390;0.353313;,
   0.005843;0.357046;,
   0.002040;0.363554;,
   0.002000;0.371090;,
   0.005734;0.377638;,
   0.998000;0.738289;,
   0.529471;0.738289;,
   0.529471;0.866186;,
   0.998000;0.866186;,
   0.998000;0.606476;,
   0.529471;0.606476;,
   0.998000;0.870103;,
   0.529471;0.870103;,
   0.998000;0.734373;,
   0.529471;0.734373;,
   0.998000;0.998000;,
   0.529471;0.998000;,
   0.529471;0.474662;,
   0.998000;0.602559;,
   0.529471;0.602559;,
   0.998000;0.474662;,
   0.005869;0.889133;,
   0.051060;0.889133;,
   0.055625;0.983528;,
   0.100816;0.983528;,
   0.052132;0.933772;,
   0.097322;0.933772;,
   0.005869;0.933772;,
   0.051060;0.933772;,
   0.023527;0.934938;,
   0.019842;0.948964;,
   0.012298;0.941528;,
   0.026342;0.945149;,
   0.016120;0.955518;,
   0.005869;0.952850;,
   0.016174;0.963055;,
   0.005962;0.965870;,
   0.019989;0.969555;,
   0.012553;0.977099;,
   0.026543;0.973277;,
   0.023875;0.983528;,
   0.034080;0.973223;,
   0.036895;0.983435;,
   0.040580;0.969408;,
   0.048124;0.976845;,
   0.044302;0.962854;,
   0.054553;0.965522;,
   0.044248;0.955317;,
   0.054460;0.952503;,
   0.040433;0.948817;,
   0.047869;0.941274;,
   0.033879;0.945095;,
   0.036547;0.934844;,
   0.262084;0.516681;,
   0.134187;0.523076;,
   0.134187;0.516681;,
   0.262084;0.523076;,
   0.134187;0.998000;,
   0.262084;0.991605;,
   0.262084;0.998000;,
   0.134187;0.991605;,
   0.394270;0.516681;,
   0.266373;0.523076;,
   0.266373;0.516681;,
   0.394270;0.523076;,
   0.266373;0.998000;,
   0.394270;0.991605;,
   0.394270;0.998000;,
   0.266373;0.991605;,
   0.129897;0.516681;,
   0.002000;0.523076;,
   0.002000;0.516681;,
   0.129897;0.523076;,
   0.002000;0.998000;,
   0.129897;0.991605;,
   0.129897;0.998000;,
   0.002000;0.991605;,
   0.526457;0.516681;,
   0.398560;0.523076;,
   0.398560;0.516681;,
   0.526457;0.523076;,
   0.398560;0.998000;,
   0.526457;0.991605;,
   0.526457;0.998000;,
   0.398560;0.991605;;
  }
 }
}

AnimationSet Anim-1 {
 

 Animation Anim-yinjing32 {
  
  { yinjing32 }

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