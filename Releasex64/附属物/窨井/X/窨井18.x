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
  "yinjing18.jpg";
 }
}

Frame yinjing18 {
 

 FrameTransformMatrix {
  1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-0.450000,-0.000000,1.000000;;
 }

 Mesh  {
  176;
  0.590000;1.998112;0.200000;,
  0.510955;1.998112;0.495000;,
  0.295000;1.998112;0.710955;,
  -0.000000;1.998112;0.790000;,
  -0.295000;1.998112;0.710955;,
  -0.510955;1.998112;0.495000;,
  -0.590000;1.998112;0.200000;,
  -0.510955;1.998112;-0.095000;,
  -0.295000;1.998112;-0.310955;,
  -0.000000;1.998112;-0.390000;,
  0.295000;1.998112;-0.310955;,
  0.510955;1.998112;-0.095000;,
  0.590000;2.450000;0.200000;,
  0.510955;2.450000;0.495000;,
  0.295000;2.450000;0.710955;,
  -0.000000;2.450000;0.790000;,
  -0.295000;2.450000;0.710955;,
  -0.510955;2.450000;0.495000;,
  -0.590000;2.450000;0.200000;,
  -0.510955;2.450000;-0.095000;,
  -0.295000;2.450000;-0.310955;,
  -0.000000;2.450000;-0.390000;,
  0.295000;2.450000;-0.310955;,
  0.510955;2.450000;-0.095000;,
  0.790000;0.000000;0.000000;,
  0.684160;0.000000;0.395000;,
  0.395000;0.000000;0.684160;,
  -0.000000;0.000000;0.790000;,
  -0.395000;0.000000;0.684160;,
  -0.684160;0.000000;0.395000;,
  -0.790000;0.000000;0.000000;,
  -0.684160;0.000000;-0.395000;,
  -0.395000;0.000000;-0.684160;,
  -0.000000;0.000000;-0.790000;,
  0.395000;0.000000;-0.684160;,
  0.684160;0.000000;-0.395000;,
  0.684160;1.648420;0.395000;,
  0.790000;1.648420;0.000000;,
  0.684160;1.648420;-0.395000;,
  0.395000;1.648420;-0.684160;,
  -0.000000;1.648420;-0.790000;,
  -0.395000;1.648420;-0.684160;,
  -0.684160;1.648420;-0.395000;,
  -0.790000;1.648420;0.000000;,
  -0.684160;1.648420;0.395000;,
  -0.395000;1.648420;0.684160;,
  -0.000000;1.648420;0.790000;,
  0.395000;1.648420;0.684160;,
  0.341534;2.450000;0.200000;,
  0.295777;2.450000;0.370767;,
  0.170767;2.450000;0.495777;,
  -0.000000;2.450000;0.541534;,
  -0.170767;2.450000;0.495777;,
  -0.295777;2.450000;0.370767;,
  -0.341534;2.450000;0.200000;,
  -0.295777;2.450000;0.029233;,
  -0.170767;2.450000;-0.095777;,
  -0.000000;2.450000;-0.141534;,
  0.170767;2.450000;-0.095777;,
  0.295777;2.450000;0.029233;,
  0.684160;0.150000;0.395000;,
  0.684160;1.498420;0.395000;,
  0.790000;1.498420;0.000000;,
  0.790000;0.150000;0.000000;,
  0.395000;0.150000;0.684160;,
  0.395000;1.498420;0.684160;,
  -0.000000;0.150000;0.790000;,
  -0.000000;1.498420;0.790000;,
  -0.395000;0.150000;0.684160;,
  -0.395000;1.498420;0.684160;,
  -0.684160;0.150000;0.395000;,
  -0.684160;1.498420;0.395000;,
  -0.790000;0.150000;0.000000;,
  -0.790000;1.498420;0.000000;,
  -0.684160;0.150000;-0.395000;,
  -0.684160;1.498420;-0.395000;,
  -0.395000;0.150000;-0.684160;,
  -0.395000;1.498420;-0.684160;,
  -0.000000;0.150000;-0.790000;,
  -0.000000;1.498420;-0.790000;,
  0.395000;0.150000;-0.684160;,
  0.395000;1.498420;-0.684160;,
  0.684160;0.150000;-0.395000;,
  0.684160;1.498420;-0.395000;,
  0.395000;0.150000;0.684160;,
  0.395000;1.498420;0.684160;,
  -0.395000;0.150000;0.684160;,
  -0.395000;1.498420;0.684160;,
  -0.395000;0.150000;-0.684160;,
  -0.395000;1.498420;-0.684160;,
  0.395000;0.150000;-0.684160;,
  0.395000;1.498420;-0.684160;,
  0.295000;2.450000;0.710955;,
  0.295000;1.998112;0.710955;,
  -0.295000;2.450000;0.710955;,
  -0.295000;1.998112;0.710955;,
  -0.295000;2.450000;-0.310955;,
  -0.295000;1.998112;-0.310955;,
  0.295000;2.450000;-0.310955;,
  0.295000;1.998112;-0.310955;,
  0.395000;1.648420;-0.684160;,
  -0.395000;1.648420;-0.684160;,
  -0.395000;1.648420;0.684160;,
  0.395000;1.648420;0.684160;,
  0.590000;2.450000;0.200000;,
  0.295777;2.450000;0.370767;,
  0.510955;2.450000;0.495000;,
  0.341534;2.450000;0.200000;,
  0.170767;2.450000;0.495777;,
  0.295000;2.450000;0.710955;,
  -0.000000;2.450000;0.541534;,
  -0.000000;2.450000;0.790000;,
  -0.170767;2.450000;0.495777;,
  -0.295000;2.450000;0.710955;,
  -0.295777;2.450000;0.370767;,
  -0.510955;2.450000;0.495000;,
  -0.341534;2.450000;0.200000;,
  -0.590000;2.450000;0.200000;,
  -0.295777;2.450000;0.029233;,
  -0.510955;2.450000;-0.095000;,
  -0.170767;2.450000;-0.095777;,
  -0.295000;2.450000;-0.310955;,
  -0.000000;2.450000;-0.141534;,
  -0.000000;2.450000;-0.390000;,
  0.170767;2.450000;-0.095777;,
  0.295000;2.450000;-0.310955;,
  0.295777;2.450000;0.029233;,
  0.510955;2.450000;-0.095000;,
  0.790000;1.498420;0.000000;,
  0.684160;1.498420;0.395000;,
  0.790000;0.000000;0.000000;,
  0.684160;0.150000;0.395000;,
  0.684160;0.000000;0.395000;,
  0.790000;0.150000;0.000000;,
  0.395000;1.498420;0.684160;,
  0.395000;0.150000;0.684160;,
  0.395000;0.000000;0.684160;,
  0.395000;1.498420;0.684160;,
  -0.000000;1.498420;0.790000;,
  0.395000;0.000000;0.684160;,
  -0.000000;0.150000;0.790000;,
  -0.000000;0.000000;0.790000;,
  0.395000;0.150000;0.684160;,
  -0.395000;1.498420;0.684160;,
  -0.395000;0.150000;0.684160;,
  -0.395000;0.000000;0.684160;,
  -0.395000;1.498420;0.684160;,
  -0.684160;1.498420;0.395000;,
  -0.395000;0.000000;0.684160;,
  -0.684160;0.150000;0.395000;,
  -0.684160;0.000000;0.395000;,
  -0.395000;0.150000;0.684160;,
  -0.790000;1.498420;0.000000;,
  -0.790000;0.150000;0.000000;,
  -0.790000;0.000000;0.000000;,
  -0.684160;1.498420;-0.395000;,
  -0.684160;0.150000;-0.395000;,
  -0.684160;0.000000;-0.395000;,
  -0.395000;1.498420;-0.684160;,
  -0.395000;0.150000;-0.684160;,
  -0.395000;0.000000;-0.684160;,
  -0.395000;1.498420;-0.684160;,
  -0.000000;1.498420;-0.790000;,
  -0.395000;0.000000;-0.684160;,
  -0.000000;0.150000;-0.790000;,
  -0.000000;0.000000;-0.790000;,
  -0.395000;0.150000;-0.684160;,
  0.395000;1.498420;-0.684160;,
  0.395000;0.150000;-0.684160;,
  0.395000;0.000000;-0.684160;,
  0.395000;1.498420;-0.684160;,
  0.684160;1.498420;-0.395000;,
  0.395000;0.000000;-0.684160;,
  0.684160;0.150000;-0.395000;,
  0.684160;0.000000;-0.395000;,
  0.395000;0.150000;-0.684160;;
  164;
  3;61,63,62;,
  3;63,61,60;,
  3;65,60,61;,
  3;60,65,64;,
  3;67,84,85;,
  3;84,67,66;,
  3;69,66,67;,
  3;66,69,68;,
  3;71,86,87;,
  3;86,71,70;,
  3;73,70,71;,
  3;70,73,72;,
  3;75,72,73;,
  3;72,75,74;,
  3;77,74,75;,
  3;74,77,76;,
  3;79,88,89;,
  3;88,79,78;,
  3;81,78,79;,
  3;78,81,80;,
  3;83,90,91;,
  3;90,83,82;,
  3;62,82,83;,
  3;82,62,63;,
  3;0,13,1;,
  3;13,0,12;,
  3;2,13,14;,
  3;13,2,1;,
  3;3,92,15;,
  3;92,3,93;,
  3;4,15,16;,
  3;15,4,3;,
  3;5,94,17;,
  3;94,5,95;,
  3;6,17,18;,
  3;17,6,5;,
  3;7,18,19;,
  3;18,7,6;,
  3;8,19,20;,
  3;19,8,7;,
  3;9,96,21;,
  3;96,9,97;,
  3;10,21,22;,
  3;21,10,9;,
  3;11,98,23;,
  3;98,11,99;,
  3;0,23,12;,
  3;23,0,11;,
  3;49,51,50;,
  3;51,53,52;,
  3;53,55,54;,
  3;51,55,53;,
  3;55,57,56;,
  3;57,59,58;,
  3;55,59,57;,
  3;51,59,55;,
  3;49,59,51;,
  3;48,59,49;,
  3;1,37,0;,
  3;37,1,36;,
  3;0,38,11;,
  3;38,0,37;,
  3;11,39,99;,
  3;39,11,38;,
  3;10,40,9;,
  3;40,10,100;,
  3;9,41,97;,
  3;41,9,40;,
  3;8,42,7;,
  3;42,8,101;,
  3;7,43,6;,
  3;43,7,42;,
  3;6,44,5;,
  3;44,6,43;,
  3;5,45,95;,
  3;45,5,44;,
  3;4,46,3;,
  3;46,4,102;,
  3;3,47,93;,
  3;47,3,46;,
  3;2,36,1;,
  3;36,2,103;,
  3;104,105,106;,
  3;105,104,107;,
  3;106,108,109;,
  3;108,106,105;,
  3;109,110,111;,
  3;110,109,108;,
  3;111,112,113;,
  3;112,111,110;,
  3;113,114,115;,
  3;114,113,112;,
  3;115,116,117;,
  3;116,115,114;,
  3;117,118,119;,
  3;118,117,116;,
  3;119,120,121;,
  3;120,119,118;,
  3;121,122,123;,
  3;122,121,120;,
  3;123,124,125;,
  3;124,123,122;,
  3;125,126,127;,
  3;126,125,124;,
  3;127,107,104;,
  3;107,127,126;,
  3;35,33,34;,
  3;33,31,32;,
  3;31,29,30;,
  3;33,29,31;,
  3;29,27,28;,
  3;27,25,26;,
  3;29,25,27;,
  3;33,25,29;,
  3;35,25,33;,
  3;24,25,35;,
  3;36,128,37;,
  3;128,36,129;,
  3;130,131,132;,
  3;131,130,133;,
  3;103,129,36;,
  3;129,103,134;,
  3;132,135,136;,
  3;135,132,131;,
  3;46,137,47;,
  3;137,46,138;,
  3;139,140,141;,
  3;140,139,142;,
  3;102,138,46;,
  3;138,102,143;,
  3;141,144,145;,
  3;144,141,140;,
  3;44,146,45;,
  3;146,44,147;,
  3;148,149,150;,
  3;149,148,151;,
  3;43,147,44;,
  3;147,43,152;,
  3;150,153,154;,
  3;153,150,149;,
  3;42,152,43;,
  3;152,42,155;,
  3;154,156,157;,
  3;156,154,153;,
  3;101,155,42;,
  3;155,101,158;,
  3;157,159,160;,
  3;159,157,156;,
  3;40,161,41;,
  3;161,40,162;,
  3;163,164,165;,
  3;164,163,166;,
  3;100,162,40;,
  3;162,100,167;,
  3;165,168,169;,
  3;168,165,164;,
  3;38,170,39;,
  3;170,38,171;,
  3;172,173,174;,
  3;173,172,175;,
  3;37,171,38;,
  3;171,37,128;,
  3;174,133,130;,
  3;133,174,173;;

  MeshNormals  {
   107;
   0.866025;0.000000;0.500000;,
   1.000000;-0.000000;-0.000000;,
   1.000000;0.000000;-0.000000;,
   0.866025;0.000000;0.500000;,
   0.500000;0.000000;0.866025;,
   0.500000;0.000000;0.866025;,
   0.000000;0.000000;1.000000;,
   -0.000000;0.000000;1.000000;,
   -0.500000;0.000000;0.866025;,
   -0.500000;0.000000;0.866025;,
   -0.866025;0.000000;0.500000;,
   -0.866025;-0.000000;0.500000;,
   -1.000000;-0.000000;0.000000;,
   -1.000000;0.000000;0.000000;,
   -0.866026;0.000000;-0.500000;,
   -0.866026;-0.000000;-0.500000;,
   -0.500000;-0.000000;-0.866025;,
   -0.500000;-0.000000;-0.866025;,
   -0.000000;-0.000000;-1.000000;,
   -0.000000;-0.000000;-1.000000;,
   0.500000;-0.000000;-0.866026;,
   0.500000;-0.000000;-0.866026;,
   0.866025;-0.000000;-0.500000;,
   0.866025;0.000000;-0.500000;,
   1.000000;0.000000;-0.000000;,
   0.866025;0.000000;0.500000;,
   0.866025;0.000000;0.500000;,
   1.000000;-0.000000;-0.000000;,
   0.500000;-0.000000;0.866026;,
   0.500000;-0.000000;0.866025;,
   0.000000;-0.000000;1.000000;,
   0.000000;-0.000000;1.000000;,
   -0.500000;-0.000000;0.866026;,
   -0.500000;-0.000000;0.866025;,
   -0.866025;0.000000;0.500000;,
   -0.866025;0.000000;0.500000;,
   -1.000000;0.000000;0.000000;,
   -1.000000;-0.000000;0.000000;,
   -0.866026;-0.000000;-0.500000;,
   -0.866026;-0.000000;-0.500000;,
   -0.500000;0.000000;-0.866025;,
   -0.500000;0.000000;-0.866025;,
   -0.000000;0.000000;-1.000000;,
   -0.000000;0.000000;-1.000000;,
   0.500000;0.000000;-0.866026;,
   0.500000;0.000000;-0.866026;,
   0.866025;-0.000000;-0.500000;,
   0.866025;-0.000000;-0.500000;,
   0.000000;1.000000;0.000000;,
   0.000000;1.000000;0.000001;,
   0.000000;1.000000;0.000000;,
   -0.000000;1.000000;0.000000;,
   -0.000000;1.000000;0.000000;,
   0.800486;0.239353;0.549483;,
   0.851980;0.520367;-0.057862;,
   0.883630;0.462005;0.075833;,
   0.855696;0.304100;0.418698;,
   0.629377;0.661536;-0.407743;,
   0.694676;0.634614;-0.338660;,
   0.324523;0.732057;-0.598980;,
   0.366642;0.725902;-0.581927;,
   -0.000000;0.752864;-0.658176;,
   -0.000000;0.752864;-0.658176;,
   -0.324524;0.732057;-0.598980;,
   -0.366643;0.725902;-0.581927;,
   -0.629378;0.661536;-0.407742;,
   -0.694677;0.634613;-0.338659;,
   -0.851980;0.520367;-0.057861;,
   -0.883630;0.462004;0.075833;,
   -0.855696;0.304099;0.418698;,
   -0.800486;0.239353;0.549483;,
   -0.536210;0.089021;0.839377;,
   -0.458250;0.063110;0.886580;,
   -0.000000;0.000000;1.000000;,
   -0.000000;0.000000;1.000000;,
   0.536210;0.089021;0.839377;,
   0.458250;0.063110;0.886580;,
   0.000000;1.000000;0.000000;,
   0.000000;1.000000;0.000001;,
   0.000000;1.000000;0.000001;,
   -0.000000;1.000000;0.000001;,
   0.000000;1.000000;0.000000;,
   0.000000;-1.000000;0.000000;,
   0.866025;0.000000;0.500000;,
   1.000000;-0.000000;-0.000000;,
   1.000000;-0.000000;-0.000000;,
   0.866025;0.000000;0.500000;,
   0.500000;0.000000;0.866025;,
   0.500000;0.000000;0.866025;,
   0.000000;0.000000;1.000000;,
   -0.000000;0.000000;1.000000;,
   -0.500000;0.000000;0.866025;,
   -0.500000;0.000000;0.866025;,
   -0.866025;0.000000;0.500000;,
   -0.866025;0.000000;0.500000;,
   -1.000000;0.000000;0.000000;,
   -1.000000;0.000000;0.000000;,
   -0.866026;0.000000;-0.500000;,
   -0.866026;0.000000;-0.500000;,
   -0.500000;0.000000;-0.866025;,
   -0.500000;0.000000;-0.866025;,
   -0.000000;-0.000000;-1.000000;,
   -0.000000;0.000000;-1.000000;,
   0.500000;-0.000000;-0.866026;,
   0.500000;0.000000;-0.866026;,
   0.866025;0.000000;-0.500000;,
   0.866025;-0.000000;-0.500000;;
   164;
   3;0,1,2;,
   3;1,0,3;,
   3;4,3,0;,
   3;3,4,5;,
   3;6,5,4;,
   3;5,6,7;,
   3;8,7,6;,
   3;7,8,9;,
   3;10,9,8;,
   3;9,10,11;,
   3;12,11,10;,
   3;11,12,13;,
   3;14,13,12;,
   3;13,14,15;,
   3;16,15,14;,
   3;15,16,17;,
   3;18,17,16;,
   3;17,18,19;,
   3;20,19,18;,
   3;19,20,21;,
   3;22,21,20;,
   3;21,22,23;,
   3;2,23,22;,
   3;23,2,1;,
   3;24,25,26;,
   3;25,24,27;,
   3;28,25,29;,
   3;25,28,26;,
   3;30,29,31;,
   3;29,30,28;,
   3;32,31,33;,
   3;31,32,30;,
   3;34,33,35;,
   3;33,34,32;,
   3;36,35,37;,
   3;35,36,34;,
   3;38,37,39;,
   3;37,38,36;,
   3;40,39,41;,
   3;39,40,38;,
   3;42,41,43;,
   3;41,42,40;,
   3;44,43,45;,
   3;43,44,42;,
   3;46,45,47;,
   3;45,46,44;,
   3;24,47,27;,
   3;47,24,46;,
   3;48,49,50;,
   3;49,51,52;,
   3;51,48,48;,
   3;49,48,51;,
   3;48,48,48;,
   3;48,48,48;,
   3;48,48,48;,
   3;49,48,48;,
   3;48,48,49;,
   3;48,48,48;,
   3;53,54,55;,
   3;54,53,56;,
   3;55,57,58;,
   3;57,55,54;,
   3;58,59,60;,
   3;59,58,57;,
   3;60,61,62;,
   3;61,60,59;,
   3;62,63,64;,
   3;63,62,61;,
   3;64,65,66;,
   3;65,64,63;,
   3;66,67,68;,
   3;67,66,65;,
   3;68,69,70;,
   3;69,68,67;,
   3;70,71,72;,
   3;71,70,69;,
   3;72,73,74;,
   3;73,72,71;,
   3;74,75,76;,
   3;75,74,73;,
   3;76,56,53;,
   3;56,76,75;,
   3;48,48,77;,
   3;48,48,48;,
   3;77,50,78;,
   3;50,77,48;,
   3;78,49,79;,
   3;49,78,50;,
   3;79,52,80;,
   3;52,79,49;,
   3;80,51,81;,
   3;51,80,52;,
   3;81,48,48;,
   3;48,81,51;,
   3;48,48,48;,
   3;48,48,48;,
   3;48,48,48;,
   3;48,48,48;,
   3;48,48,48;,
   3;48,48,48;,
   3;48,48,48;,
   3;48,48,48;,
   3;48,48,48;,
   3;48,48,48;,
   3;48,48,48;,
   3;48,48,48;,
   3;82,82,82;,
   3;82,82,82;,
   3;82,82,82;,
   3;82,82,82;,
   3;82,82,82;,
   3;82,82,82;,
   3;82,82,82;,
   3;82,82,82;,
   3;82,82,82;,
   3;82,82,82;,
   3;83,2,84;,
   3;2,83,0;,
   3;85,3,86;,
   3;3,85,1;,
   3;87,0,83;,
   3;0,87,4;,
   3;86,5,88;,
   3;5,86,3;,
   3;89,4,87;,
   3;4,89,6;,
   3;88,7,90;,
   3;7,88,5;,
   3;91,6,89;,
   3;6,91,8;,
   3;90,9,92;,
   3;9,90,7;,
   3;93,8,91;,
   3;8,93,10;,
   3;92,11,94;,
   3;11,92,9;,
   3;95,10,93;,
   3;10,95,12;,
   3;94,13,96;,
   3;13,94,11;,
   3;97,12,95;,
   3;12,97,14;,
   3;96,15,98;,
   3;15,96,13;,
   3;99,14,97;,
   3;14,99,16;,
   3;98,17,100;,
   3;17,98,15;,
   3;101,16,99;,
   3;16,101,18;,
   3;100,19,102;,
   3;19,100,17;,
   3;103,18,101;,
   3;18,103,20;,
   3;102,21,104;,
   3;21,102,19;,
   3;105,20,103;,
   3;20,105,22;,
   3;104,23,106;,
   3;23,104,21;,
   3;84,22,105;,
   3;22,84,2;,
   3;106,1,85;,
   3;1,106,23;;
  }

  MeshMaterialList  {
   1;
   164;
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
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
   176;
   0.077269;0.701724;,
   0.033812;0.701724;,
   0.002000;0.701724;,
   0.480145;0.931432;,
   0.436688;0.931432;,
   0.385681;0.701724;,
   0.342224;0.701724;,
   0.298768;0.701724;,
   0.266956;0.701724;,
   0.600984;0.931432;,
   0.557527;0.931432;,
   0.120725;0.701724;,
   0.077269;0.768292;,
   0.033812;0.768292;,
   0.002000;0.768292;,
   0.480145;0.998000;,
   0.436688;0.998000;,
   0.385681;0.768292;,
   0.342224;0.768292;,
   0.298768;0.768292;,
   0.266956;0.768292;,
   0.600984;0.998000;,
   0.557527;0.998000;,
   0.120725;0.768292;,
   0.422388;0.550927;,
   0.421957;0.490689;,
   0.451704;0.438305;,
   0.503656;0.407813;,
   0.563895;0.407382;,
   0.616278;0.437128;,
   0.646771;0.489081;,
   0.647202;0.549319;,
   0.617455;0.601703;,
   0.565503;0.632195;,
   0.505264;0.632626;,
   0.452881;0.602880;,
   0.048543;0.650211;,
   0.106731;0.650211;,
   0.164918;0.650211;,
   0.207515;0.650211;,
   0.600984;0.879919;,
   0.659171;0.879919;,
   0.254575;0.650211;,
   0.312762;0.650211;,
   0.370950;0.650211;,
   0.413546;0.650211;,
   0.480145;0.879919;,
   0.538332;0.879919;,
   0.063944;0.431204;,
   0.037902;0.431066;,
   0.015279;0.443968;,
   0.002138;0.466453;,
   0.002000;0.492495;,
   0.014902;0.515118;,
   0.037386;0.528259;,
   0.063429;0.528397;,
   0.086052;0.515495;,
   0.099193;0.493011;,
   0.099331;0.466968;,
   0.086429;0.444345;,
   0.361740;0.200636;,
   0.361740;0.002000;,
   0.303552;0.002000;,
   0.303552;0.200636;,
   0.404336;0.200636;,
   0.404336;0.002000;,
   0.200636;0.060188;,
   0.002000;0.060188;,
   0.200636;0.002000;,
   0.002000;0.002000;,
   0.245365;0.401404;,
   0.245365;0.202768;,
   0.303552;0.401404;,
   0.303552;0.202768;,
   0.361740;0.401404;,
   0.361740;0.202768;,
   0.404336;0.401404;,
   0.404336;0.202768;,
   0.200636;0.260956;,
   0.002000;0.260956;,
   0.200636;0.202768;,
   0.002000;0.202768;,
   0.245364;0.200636;,
   0.245364;0.002000;,
   0.200636;0.118375;,
   0.002000;0.118375;,
   0.202768;0.401404;,
   0.202768;0.202768;,
   0.200636;0.319143;,
   0.002000;0.319143;,
   0.202768;0.200636;,
   0.202768;0.002000;,
   0.523601;0.998000;,
   0.523601;0.931432;,
   0.417493;0.768292;,
   0.417493;0.701724;,
   0.644440;0.998000;,
   0.644440;0.931432;,
   0.152538;0.768292;,
   0.152538;0.701724;,
   0.542796;0.879919;,
   0.211979;0.650211;,
   0.421957;0.879919;,
   0.005947;0.650211;,
   0.063016;0.773077;,
   0.050281;0.821546;,
   0.024215;0.795850;,
   0.072741;0.808363;,
   0.037421;0.844192;,
   0.002000;0.834972;,
   0.037608;0.870235;,
   0.002322;0.879960;,
   0.050790;0.892695;,
   0.025095;0.918761;,
   0.073437;0.905555;,
   0.064216;0.940976;,
   0.099479;0.905369;,
   0.109205;0.940654;,
   0.121939;0.892186;,
   0.148005;0.917882;,
   0.134799;0.869539;,
   0.170220;0.878760;,
   0.134613;0.843497;,
   0.169899;0.833771;,
   0.121430;0.821037;,
   0.147126;0.794971;,
   0.098784;0.808177;,
   0.108004;0.772756;,
   0.106731;0.628114;,
   0.048543;0.628114;,
   0.106731;0.407382;,
   0.048543;0.429478;,
   0.048543;0.407382;,
   0.106731;0.429478;,
   0.005947;0.628114;,
   0.005947;0.429478;,
   0.005947;0.407382;,
   0.538332;0.857823;,
   0.480145;0.857823;,
   0.538332;0.637090;,
   0.480145;0.659187;,
   0.480145;0.637090;,
   0.538332;0.659187;,
   0.421957;0.857823;,
   0.421957;0.659187;,
   0.421957;0.637090;,
   0.413546;0.628114;,
   0.370950;0.628114;,
   0.413546;0.407382;,
   0.370950;0.429478;,
   0.370950;0.407382;,
   0.413546;0.429478;,
   0.312762;0.628114;,
   0.312762;0.429478;,
   0.312762;0.407382;,
   0.254575;0.628114;,
   0.254575;0.429478;,
   0.254575;0.407382;,
   0.211979;0.628114;,
   0.211979;0.429478;,
   0.211979;0.407382;,
   0.659171;0.857823;,
   0.600984;0.857823;,
   0.659171;0.637090;,
   0.600984;0.659187;,
   0.600984;0.637090;,
   0.659171;0.659187;,
   0.542796;0.857823;,
   0.542796;0.659187;,
   0.542796;0.637090;,
   0.207515;0.628114;,
   0.164918;0.628114;,
   0.207515;0.407382;,
   0.164918;0.429478;,
   0.164918;0.407382;,
   0.207515;0.429478;;
  }
 }
}

AnimationSet Anim-1 {
 

 Animation Anim-yinjing18 {
  
  { yinjing18 }

  AnimationKey {
   4;
   101;
   0;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-0.450000,-0.000000,1.000000;;,
   160;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-0.450000,-0.000000,1.000000;;,
   320;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-0.450000,-0.000000,1.000000;;,
   480;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-0.450000,-0.000000,1.000000;;,
   640;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-0.450000,-0.000000,1.000000;;,
   800;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-0.450000,-0.000000,1.000000;;,
   960;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-0.450000,-0.000000,1.000000;;,
   1120;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-0.450000,-0.000000,1.000000;;,
   1280;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-0.450000,-0.000000,1.000000;;,
   1440;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-0.450000,-0.000000,1.000000;;,
   1600;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-0.450000,-0.000000,1.000000;;,
   1760;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-0.450000,-0.000000,1.000000;;,
   1920;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-0.450000,-0.000000,1.000000;;,
   2080;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-0.450000,-0.000000,1.000000;;,
   2240;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-0.450000,-0.000000,1.000000;;,
   2400;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-0.450000,-0.000000,1.000000;;,
   2560;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-0.450000,-0.000000,1.000000;;,
   2720;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-0.450000,-0.000000,1.000000;;,
   2880;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-0.450000,-0.000000,1.000000;;,
   3040;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-0.450000,-0.000000,1.000000;;,
   3200;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-0.450000,-0.000000,1.000000;;,
   3360;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-0.450000,-0.000000,1.000000;;,
   3520;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-0.450000,-0.000000,1.000000;;,
   3680;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-0.450000,-0.000000,1.000000;;,
   3840;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-0.450000,-0.000000,1.000000;;,
   4000;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-0.450000,-0.000000,1.000000;;,
   4160;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-0.450000,-0.000000,1.000000;;,
   4320;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-0.450000,-0.000000,1.000000;;,
   4480;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-0.450000,-0.000000,1.000000;;,
   4640;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-0.450000,-0.000000,1.000000;;,
   4800;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-0.450000,-0.000000,1.000000;;,
   4960;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-0.450000,-0.000000,1.000000;;,
   5120;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-0.450000,-0.000000,1.000000;;,
   5280;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-0.450000,-0.000000,1.000000;;,
   5440;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-0.450000,-0.000000,1.000000;;,
   5600;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-0.450000,-0.000000,1.000000;;,
   5760;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-0.450000,-0.000000,1.000000;;,
   5920;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-0.450000,-0.000000,1.000000;;,
   6080;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-0.450000,-0.000000,1.000000;;,
   6240;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-0.450000,-0.000000,1.000000;;,
   6400;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-0.450000,-0.000000,1.000000;;,
   6560;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-0.450000,-0.000000,1.000000;;,
   6720;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-0.450000,-0.000000,1.000000;;,
   6880;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-0.450000,-0.000000,1.000000;;,
   7040;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-0.450000,-0.000000,1.000000;;,
   7200;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-0.450000,-0.000000,1.000000;;,
   7360;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-0.450000,-0.000000,1.000000;;,
   7520;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-0.450000,-0.000000,1.000000;;,
   7680;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-0.450000,-0.000000,1.000000;;,
   7840;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-0.450000,-0.000000,1.000000;;,
   8000;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-0.450000,-0.000000,1.000000;;,
   8160;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-0.450000,-0.000000,1.000000;;,
   8320;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-0.450000,-0.000000,1.000000;;,
   8480;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-0.450000,-0.000000,1.000000;;,
   8640;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-0.450000,-0.000000,1.000000;;,
   8800;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-0.450000,-0.000000,1.000000;;,
   8960;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-0.450000,-0.000000,1.000000;;,
   9120;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-0.450000,-0.000000,1.000000;;,
   9280;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-0.450000,-0.000000,1.000000;;,
   9440;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-0.450000,-0.000000,1.000000;;,
   9600;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-0.450000,-0.000000,1.000000;;,
   9760;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-0.450000,-0.000000,1.000000;;,
   9920;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-0.450000,-0.000000,1.000000;;,
   10080;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-0.450000,-0.000000,1.000000;;,
   10240;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-0.450000,-0.000000,1.000000;;,
   10400;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-0.450000,-0.000000,1.000000;;,
   10560;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-0.450000,-0.000000,1.000000;;,
   10720;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-0.450000,-0.000000,1.000000;;,
   10880;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-0.450000,-0.000000,1.000000;;,
   11040;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-0.450000,-0.000000,1.000000;;,
   11200;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-0.450000,-0.000000,1.000000;;,
   11360;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-0.450000,-0.000000,1.000000;;,
   11520;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-0.450000,-0.000000,1.000000;;,
   11680;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-0.450000,-0.000000,1.000000;;,
   11840;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-0.450000,-0.000000,1.000000;;,
   12000;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-0.450000,-0.000000,1.000000;;,
   12160;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-0.450000,-0.000000,1.000000;;,
   12320;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-0.450000,-0.000000,1.000000;;,
   12480;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-0.450000,-0.000000,1.000000;;,
   12640;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-0.450000,-0.000000,1.000000;;,
   12800;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-0.450000,-0.000000,1.000000;;,
   12960;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-0.450000,-0.000000,1.000000;;,
   13120;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-0.450000,-0.000000,1.000000;;,
   13280;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-0.450000,-0.000000,1.000000;;,
   13440;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-0.450000,-0.000000,1.000000;;,
   13600;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-0.450000,-0.000000,1.000000;;,
   13760;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-0.450000,-0.000000,1.000000;;,
   13920;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-0.450000,-0.000000,1.000000;;,
   14080;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-0.450000,-0.000000,1.000000;;,
   14240;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-0.450000,-0.000000,1.000000;;,
   14400;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-0.450000,-0.000000,1.000000;;,
   14560;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-0.450000,-0.000000,1.000000;;,
   14720;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-0.450000,-0.000000,1.000000;;,
   14880;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-0.450000,-0.000000,1.000000;;,
   15040;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-0.450000,-0.000000,1.000000;;,
   15200;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-0.450000,-0.000000,1.000000;;,
   15360;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-0.450000,-0.000000,1.000000;;,
   15520;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-0.450000,-0.000000,1.000000;;,
   15680;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-0.450000,-0.000000,1.000000;;,
   15840;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-0.450000,-0.000000,1.000000;;,
   16000;16;1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-0.450000,-0.000000,1.000000;;;
  }
 }
}