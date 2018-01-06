xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header{
1;
0;
1;
}

Mesh {
 199;
 0.00000;3.00000;-0.12000;,
 0.08485;3.00000;-0.08485;,
 0.08485;0.00000;-0.08485;,
 0.00000;0.00000;-0.12000;,
 0.12000;3.00000;0.00000;,
 0.12000;0.00000;0.00000;,
 0.08485;3.00000;0.08485;,
 0.08485;0.00000;0.08485;,
 -0.00000;3.00000;0.12000;,
 -0.00000;0.00000;0.12000;,
 -0.08485;3.00000;0.08485;,
 -0.08485;0.00000;0.08485;,
 -0.12000;3.00000;-0.00000;,
 -0.12000;0.00000;-0.00000;,
 -0.08485;3.00000;-0.08485;,
 -0.08485;0.00000;-0.08485;,
 0.00000;3.00000;-0.12000;,
 0.00000;0.00000;-0.12000;,
 0.00000;3.00000;0.00000;,
 0.00000;3.00000;0.00000;,
 0.00000;3.00000;0.00000;,
 0.00000;3.00000;0.00000;,
 0.00000;3.00000;0.00000;,
 0.00000;3.00000;0.00000;,
 0.00000;3.00000;0.00000;,
 0.00000;3.00000;0.00000;,
 0.00000;0.00000;0.00000;,
 0.00000;0.00000;0.00000;,
 0.00000;0.00000;0.00000;,
 0.00000;0.00000;0.00000;,
 0.00000;0.00000;0.00000;,
 0.00000;0.00000;0.00000;,
 0.00000;0.00000;0.00000;,
 0.00000;0.00000;0.00000;,
 0.00000;3.30000;0.00000;,
 0.08118;3.27716;-0.08118;,
 0.00000;3.27716;-0.11481;,
 0.00000;3.30000;0.00000;,
 0.11481;3.27716;0.00000;,
 0.00000;3.30000;0.00000;,
 0.08118;3.27716;0.08118;,
 0.00000;3.30000;0.00000;,
 -0.00000;3.27716;0.11481;,
 0.00000;3.30000;0.00000;,
 -0.08118;3.27716;0.08118;,
 0.00000;3.30000;0.00000;,
 -0.11481;3.27716;-0.00000;,
 0.00000;3.30000;0.00000;,
 -0.08118;3.27716;-0.08118;,
 0.00000;3.30000;0.00000;,
 0.00000;3.27716;-0.11481;,
 0.15000;3.21213;-0.15000;,
 0.00000;3.21213;-0.21213;,
 0.21213;3.21213;0.00000;,
 0.15000;3.21213;0.15000;,
 -0.00000;3.21213;0.21213;,
 -0.15000;3.21213;0.15000;,
 -0.21213;3.21213;-0.00000;,
 -0.15000;3.21213;-0.15000;,
 0.00000;3.21213;-0.21213;,
 0.19598;3.11480;-0.19598;,
 0.00000;3.11480;-0.27716;,
 0.27716;3.11480;0.00000;,
 0.19598;3.11480;0.19598;,
 -0.00000;3.11480;0.27716;,
 -0.19598;3.11480;0.19598;,
 -0.27716;3.11480;-0.00000;,
 -0.19598;3.11480;-0.19598;,
 0.00000;3.11480;-0.27716;,
 0.21213;3.00000;-0.21213;,
 0.00000;3.00000;-0.30000;,
 0.30000;3.00000;0.00000;,
 0.21213;3.00000;0.21213;,
 -0.00000;3.00000;0.30000;,
 -0.21213;3.00000;0.21213;,
 -0.30000;3.00000;-0.00000;,
 -0.21213;3.00000;-0.21213;,
 0.00000;3.00000;-0.30000;,
 0.19598;2.88519;-0.19598;,
 0.00000;2.88519;-0.27716;,
 0.27716;2.88519;0.00000;,
 0.19598;2.88519;0.19598;,
 -0.00000;2.88519;0.27716;,
 -0.19598;2.88519;0.19598;,
 -0.27716;2.88519;-0.00000;,
 -0.19598;2.88519;-0.19598;,
 0.00000;2.88519;-0.27716;,
 0.15000;2.78787;-0.15000;,
 0.00000;2.78787;-0.21213;,
 0.21213;2.78787;0.00000;,
 0.15000;2.78787;0.15000;,
 -0.00000;2.78787;0.21213;,
 -0.15000;2.78787;0.15000;,
 -0.21213;2.78787;-0.00000;,
 -0.15000;2.78787;-0.15000;,
 0.00000;2.78787;-0.21213;,
 0.08118;2.72284;-0.08118;,
 0.00000;2.72284;-0.11481;,
 0.11481;2.72284;0.00000;,
 0.08118;2.72284;0.08118;,
 -0.00000;2.72284;0.11481;,
 -0.08118;2.72284;0.08118;,
 -0.11481;2.72284;-0.00000;,
 -0.08118;2.72284;-0.08118;,
 0.00000;2.72284;-0.11481;,
 0.00000;2.70000;0.00000;,
 0.00000;2.70000;0.00000;,
 0.00000;2.70000;0.00000;,
 0.00000;2.70000;0.00000;,
 0.00000;2.70000;0.00000;,
 0.00000;2.70000;0.00000;,
 0.00000;2.70000;0.00000;,
 0.00000;2.70000;0.00000;,
 0.00000;2.70000;-0.03000;,
 1.80000;2.70000;-0.03000;,
 1.80000;1.50000;-0.03000;,
 0.00000;1.50000;-0.03000;,
 1.80000;2.70000;-0.03000;,
 1.80000;2.70000;0.03000;,
 1.80000;1.50000;0.03000;,
 1.80000;1.50000;-0.03000;,
 1.80000;2.70000;0.03000;,
 0.00000;2.70000;0.03000;,
 0.00000;1.50000;0.03000;,
 1.80000;1.50000;0.03000;,
 0.00000;2.70000;0.03000;,
 0.00000;2.70000;-0.03000;,
 0.00000;1.50000;-0.03000;,
 0.00000;1.50000;0.03000;,
 1.80000;2.70000;-0.03000;,
 0.00000;2.70000;-0.03000;,
 0.00000;1.50000;-0.03000;,
 1.80000;1.50000;-0.03000;,
 0.00000;0.30000;-1.50000;,
 0.57403;0.30000;-1.38582;,
 0.57403;0.00000;-1.38582;,
 0.00000;0.00000;-1.50000;,
 1.06066;0.30000;-1.06066;,
 1.06066;0.00000;-1.06066;,
 1.38582;0.30000;-0.57403;,
 1.38582;0.00000;-0.57403;,
 1.50000;0.30000;0.00000;,
 1.50000;0.00000;0.00000;,
 1.38582;0.30000;0.57403;,
 1.38582;0.00000;0.57403;,
 1.06066;0.30000;1.06066;,
 1.06066;0.00000;1.06066;,
 0.57403;0.30000;1.38582;,
 0.57403;0.00000;1.38582;,
 0.00000;0.30000;1.50000;,
 0.00000;0.00000;1.50000;,
 -0.57402;0.30000;1.38582;,
 -0.57402;0.00000;1.38582;,
 -1.06066;0.30000;1.06066;,
 -1.06066;0.00000;1.06066;,
 -1.38582;0.30000;0.57403;,
 -1.38582;0.00000;0.57403;,
 -1.50000;0.30000;-0.00000;,
 -1.50000;0.00000;-0.00000;,
 -1.38582;0.30000;-0.57403;,
 -1.38582;0.00000;-0.57403;,
 -1.06066;0.30000;-1.06066;,
 -1.06066;0.00000;-1.06066;,
 -0.57402;0.30000;-1.38582;,
 -0.57402;0.00000;-1.38582;,
 0.00000;0.30000;-1.50000;,
 0.00000;0.00000;-1.50000;,
 0.00000;0.30000;0.00000;,
 0.00000;0.30000;0.00000;,
 0.00000;0.30000;0.00000;,
 0.00000;0.30000;0.00000;,
 0.00000;0.30000;0.00000;,
 0.00000;0.30000;0.00000;,
 0.00000;0.30000;0.00000;,
 0.00000;0.30000;0.00000;,
 0.00000;0.30000;0.00000;,
 0.00000;0.30000;0.00000;,
 0.00000;0.30000;0.00000;,
 0.00000;0.30000;0.00000;,
 0.00000;0.30000;0.00000;,
 0.00000;0.30000;0.00000;,
 0.00000;0.30000;0.00000;,
 0.00000;0.30000;0.00000;,
 0.00000;0.00000;0.00000;,
 0.00000;0.00000;0.00000;,
 0.00000;0.00000;0.00000;,
 0.00000;0.00000;0.00000;,
 0.00000;0.00000;0.00000;,
 0.00000;0.00000;0.00000;,
 0.00000;0.00000;0.00000;,
 0.00000;0.00000;0.00000;,
 0.00000;0.00000;0.00000;,
 0.00000;0.00000;0.00000;,
 0.00000;0.00000;0.00000;,
 0.00000;0.00000;0.00000;,
 0.00000;0.00000;0.00000;,
 0.00000;0.00000;0.00000;,
 0.00000;0.00000;0.00000;,
 0.00000;0.00000;0.00000;;
 
 142;
 4;0,1,2,3;,
 4;1,4,5,2;,
 4;4,6,7,5;,
 4;6,8,9,7;,
 4;8,10,11,9;,
 4;10,12,13,11;,
 4;12,14,15,13;,
 4;14,16,17,15;,
 3;18,1,0;,
 3;19,4,1;,
 3;20,6,4;,
 3;21,8,6;,
 3;22,10,8;,
 3;23,12,10;,
 3;24,14,12;,
 3;25,16,14;,
 3;26,3,2;,
 3;27,2,5;,
 3;28,5,7;,
 3;29,7,9;,
 3;30,9,11;,
 3;31,11,13;,
 3;32,13,15;,
 3;33,15,17;,
 3;34,35,36;,
 3;37,38,35;,
 3;39,40,38;,
 3;41,42,40;,
 3;43,44,42;,
 3;45,46,44;,
 3;47,48,46;,
 3;49,50,48;,
 4;36,35,51,52;,
 4;35,38,53,51;,
 4;38,40,54,53;,
 4;40,42,55,54;,
 4;42,44,56,55;,
 4;44,46,57,56;,
 4;46,48,58,57;,
 4;48,50,59,58;,
 4;52,51,60,61;,
 4;51,53,62,60;,
 4;53,54,63,62;,
 4;54,55,64,63;,
 4;55,56,65,64;,
 4;56,57,66,65;,
 4;57,58,67,66;,
 4;58,59,68,67;,
 4;61,60,69,70;,
 4;60,62,71,69;,
 4;62,63,72,71;,
 4;63,64,73,72;,
 4;64,65,74,73;,
 4;65,66,75,74;,
 4;66,67,76,75;,
 4;67,68,77,76;,
 4;70,69,78,79;,
 4;69,71,80,78;,
 4;71,72,81,80;,
 4;72,73,82,81;,
 4;73,74,83,82;,
 4;74,75,84,83;,
 4;75,76,85,84;,
 4;76,77,86,85;,
 4;79,78,87,88;,
 4;78,80,89,87;,
 4;80,81,90,89;,
 4;81,82,91,90;,
 4;82,83,92,91;,
 4;83,84,93,92;,
 4;84,85,94,93;,
 4;85,86,95,94;,
 4;88,87,96,97;,
 4;87,89,98,96;,
 4;89,90,99,98;,
 4;90,91,100,99;,
 4;91,92,101,100;,
 4;92,93,102,101;,
 4;93,94,103,102;,
 4;94,95,104,103;,
 3;97,96,105;,
 3;96,98,106;,
 3;98,99,107;,
 3;99,100,108;,
 3;100,101,109;,
 3;101,102,110;,
 3;102,103,111;,
 3;103,104,112;,
 4;113,114,115,116;,
 4;117,118,119,120;,
 4;121,122,123,124;,
 4;125,126,127,128;,
 4;125,118,129,130;,
 4;131,132,119,128;,
 4;133,134,135,136;,
 4;134,137,138,135;,
 4;137,139,140,138;,
 4;139,141,142,140;,
 4;141,143,144,142;,
 4;143,145,146,144;,
 4;145,147,148,146;,
 4;147,149,150,148;,
 4;149,151,152,150;,
 4;151,153,154,152;,
 4;153,155,156,154;,
 4;155,157,158,156;,
 4;157,159,160,158;,
 4;159,161,162,160;,
 4;161,163,164,162;,
 4;163,165,166,164;,
 3;167,134,133;,
 3;168,137,134;,
 3;169,139,137;,
 3;170,141,139;,
 3;171,143,141;,
 3;172,145,143;,
 3;173,147,145;,
 3;174,149,147;,
 3;175,151,149;,
 3;176,153,151;,
 3;177,155,153;,
 3;178,157,155;,
 3;179,159,157;,
 3;180,161,159;,
 3;181,163,161;,
 3;182,165,163;,
 3;183,136,135;,
 3;184,135,138;,
 3;185,138,140;,
 3;186,140,142;,
 3;187,142,144;,
 3;188,144,146;,
 3;189,146,148;,
 3;190,148,150;,
 3;191,150,152;,
 3;192,152,154;,
 3;193,154,156;,
 3;194,156,158;,
 3;195,158,160;,
 3;196,160,162;,
 3;197,162,164;,
 3;198,164,166;;
 
 MeshMaterialList {
  4;
  142;
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  0,
  0,
  0,
  0,
  0,
  0,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2;;
  Material {
   0.600000;0.294118;0.058824;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.400000;0.196078;0.039216;;
  }
  Material {
   0.176471;0.176471;0.176471;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.117647;0.117647;0.117647;;
  }
  Material {
   0.230588;0.442353;0.496471;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.153725;0.294902;0.330980;;
  }
  Material {
   1.000000;1.000000;1.000000;1.000000;;
   0.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  90;
  0.000000;1.000000;0.000000;,
  -0.000000;0.000000;-1.000000;,
  0.707107;0.000000;-0.707107;,
  1.000000;0.000000;0.000000;,
  0.707107;0.000000;0.707107;,
  -0.000000;0.000000;1.000000;,
  -0.707107;0.000000;0.707107;,
  -1.000000;0.000000;0.000000;,
  -0.707107;0.000000;-0.707107;,
  0.000000;-1.000000;-0.000000;,
  -0.000000;1.000000;0.000000;,
  -0.000000;0.924735;-0.380611;,
  0.269133;0.924735;-0.269133;,
  0.380611;0.924735;0.000000;,
  0.269133;0.924735;0.269133;,
  -0.000000;0.924735;0.380611;,
  -0.269133;0.924735;0.269132;,
  -0.380611;0.924735;0.000000;,
  -0.269133;0.924735;-0.269133;,
  -0.000000;0.709231;-0.704976;,
  0.498494;0.709231;-0.498494;,
  0.704976;0.709231;0.000000;,
  0.498494;0.709231;0.498494;,
  -0.000000;0.709231;0.704976;,
  -0.498494;0.709231;0.498494;,
  -0.704976;0.709231;0.000000;,
  -0.498494;0.709231;-0.498494;,
  -0.000000;0.384551;-0.923104;,
  0.652733;0.384551;-0.652733;,
  0.923104;0.384551;0.000000;,
  0.652733;0.384551;0.652733;,
  -0.000000;0.384551;0.923104;,
  -0.652733;0.384551;0.652733;,
  -0.923104;0.384551;0.000000;,
  -0.652733;0.384551;-0.652733;,
  -0.000000;0.000000;-1.000000;,
  1.000000;0.000000;0.000000;,
  -0.000000;0.000000;1.000000;,
  -0.707107;0.000000;0.707107;,
  -1.000000;-0.000000;0.000000;,
  -0.707107;0.000000;-0.707107;,
  -0.000000;-0.384551;-0.923104;,
  0.652733;-0.384551;-0.652733;,
  0.923104;-0.384551;0.000000;,
  0.652733;-0.384551;0.652733;,
  -0.000000;-0.384551;0.923104;,
  -0.652733;-0.384551;0.652733;,
  -0.923104;-0.384551;0.000000;,
  -0.652733;-0.384551;-0.652733;,
  -0.000000;-0.709231;-0.704976;,
  0.498494;-0.709231;-0.498494;,
  0.704976;-0.709231;0.000000;,
  0.498494;-0.709231;0.498494;,
  -0.000000;-0.709231;0.704976;,
  -0.498494;-0.709231;0.498494;,
  -0.704977;-0.709231;0.000000;,
  -0.498494;-0.709231;-0.498494;,
  -0.000000;-0.924735;-0.380611;,
  0.269133;-0.924735;-0.269133;,
  0.380611;-0.924735;0.000000;,
  0.269133;-0.924735;0.269133;,
  -0.000000;-0.924735;0.380611;,
  -0.269133;-0.924735;0.269133;,
  -0.380611;-0.924735;-0.000000;,
  -0.269133;-0.924735;-0.269132;,
  0.000000;-1.000000;-0.000000;,
  0.000000;0.000000;-1.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;0.000000;-1.000000;,
  0.382683;0.000000;-0.923880;,
  0.707107;0.000000;-0.707107;,
  0.923880;0.000000;-0.382683;,
  1.000000;0.000000;0.000000;,
  0.923880;0.000000;0.382683;,
  0.707107;0.000000;0.707107;,
  0.382683;0.000000;0.923880;,
  0.000000;0.000000;1.000000;,
  -0.382683;0.000000;0.923880;,
  -0.707107;0.000000;0.707107;,
  -0.923879;0.000000;0.382684;,
  -1.000000;0.000000;0.000000;,
  -0.923879;0.000000;-0.382684;,
  -0.707107;0.000000;-0.707107;,
  -0.382683;0.000000;-0.923880;,
  0.000000;-1.000000;-0.000000;;
  142;
  4;1,2,2,1;,
  4;2,3,3,2;,
  4;3,4,4,3;,
  4;4,5,5,4;,
  4;5,6,6,5;,
  4;6,7,7,6;,
  4;7,8,8,7;,
  4;8,1,1,8;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,9,9;,
  3;10,12,11;,
  3;10,13,12;,
  3;10,14,13;,
  3;10,15,14;,
  3;10,16,15;,
  3;10,17,16;,
  3;10,18,17;,
  3;10,11,18;,
  4;11,12,20,19;,
  4;12,13,21,20;,
  4;13,14,22,21;,
  4;14,15,23,22;,
  4;15,16,24,23;,
  4;16,17,25,24;,
  4;17,18,26,25;,
  4;18,11,19,26;,
  4;19,20,28,27;,
  4;20,21,29,28;,
  4;21,22,30,29;,
  4;22,23,31,30;,
  4;23,24,32,31;,
  4;24,25,33,32;,
  4;25,26,34,33;,
  4;26,19,27,34;,
  4;27,28,2,35;,
  4;28,29,36,2;,
  4;29,30,4,36;,
  4;30,31,37,4;,
  4;31,32,38,37;,
  4;32,33,39,38;,
  4;33,34,40,39;,
  4;34,27,35,40;,
  4;35,2,42,41;,
  4;2,36,43,42;,
  4;36,4,44,43;,
  4;4,37,45,44;,
  4;37,38,46,45;,
  4;38,39,47,46;,
  4;39,40,48,47;,
  4;40,35,41,48;,
  4;41,42,50,49;,
  4;42,43,51,50;,
  4;43,44,52,51;,
  4;44,45,53,52;,
  4;45,46,54,53;,
  4;46,47,55,54;,
  4;47,48,56,55;,
  4;48,41,49,56;,
  4;49,50,58,57;,
  4;50,51,59,58;,
  4;51,52,60,59;,
  4;52,53,61,60;,
  4;53,54,62,61;,
  4;54,55,63,62;,
  4;55,56,64,63;,
  4;56,49,57,64;,
  3;57,58,65;,
  3;58,59,65;,
  3;59,60,65;,
  3;60,61,65;,
  3;61,62,65;,
  3;62,63,65;,
  3;63,64,65;,
  3;64,57,65;,
  4;66,66,66,66;,
  4;67,67,67,67;,
  4;68,68,68,68;,
  4;69,69,69,69;,
  4;70,70,70,70;,
  4;71,71,71,71;,
  4;73,74,74,73;,
  4;74,75,75,74;,
  4;75,76,76,75;,
  4;76,77,77,76;,
  4;77,78,78,77;,
  4;78,79,79,78;,
  4;79,80,80,79;,
  4;80,81,81,80;,
  4;81,82,82,81;,
  4;82,83,83,82;,
  4;83,84,84,83;,
  4;84,85,85,84;,
  4;85,86,86,85;,
  4;86,87,87,86;,
  4;87,88,88,87;,
  4;88,73,73,88;,
  3;72,72,72;,
  3;72,72,72;,
  3;72,72,72;,
  3;72,72,72;,
  3;72,72,72;,
  3;72,72,72;,
  3;72,72,72;,
  3;72,72,72;,
  3;72,72,72;,
  3;72,72,72;,
  3;72,72,72;,
  3;72,72,72;,
  3;72,72,72;,
  3;72,72,72;,
  3;72,72,72;,
  3;72,72,72;,
  3;89,89,89;,
  3;89,89,89;,
  3;89,89,89;,
  3;89,89,89;,
  3;89,89,89;,
  3;89,89,89;,
  3;89,89,89;,
  3;89,89,89;,
  3;89,89,89;,
  3;89,89,89;,
  3;89,89,89;,
  3;89,89,89;,
  3;89,89,89;,
  3;89,89,89;,
  3;89,89,89;,
  3;89,89,89;;
 }
 MeshTextureCoords {
  199;
  0.000000;0.000000;,
  0.125000;0.000000;,
  0.125000;1.000000;,
  0.000000;1.000000;,
  0.250000;0.000000;,
  0.250000;1.000000;,
  0.375000;0.000000;,
  0.375000;1.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.625000;0.000000;,
  0.625000;1.000000;,
  0.750000;0.000000;,
  0.750000;1.000000;,
  0.875000;0.000000;,
  0.875000;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.062500;0.000000;,
  0.187500;0.000000;,
  0.312500;0.000000;,
  0.437500;0.000000;,
  0.562500;0.000000;,
  0.687500;0.000000;,
  0.812500;0.000000;,
  0.937500;0.000000;,
  0.062500;1.000000;,
  0.187500;1.000000;,
  0.312500;1.000000;,
  0.437500;1.000000;,
  0.562500;1.000000;,
  0.687500;1.000000;,
  0.812500;1.000000;,
  0.937500;1.000000;,
  0.062500;0.000000;,
  0.125000;0.125000;,
  0.000000;0.125000;,
  0.187500;0.000000;,
  0.250000;0.125000;,
  0.312500;0.000000;,
  0.375000;0.125000;,
  0.437500;0.000000;,
  0.500000;0.125000;,
  0.562500;0.000000;,
  0.625000;0.125000;,
  0.687500;0.000000;,
  0.750000;0.125000;,
  0.812500;0.000000;,
  0.875000;0.125000;,
  0.937500;0.000000;,
  1.000000;0.125000;,
  0.125000;0.250000;,
  0.000000;0.250000;,
  0.250000;0.250000;,
  0.375000;0.250000;,
  0.500000;0.250000;,
  0.625000;0.250000;,
  0.750000;0.250000;,
  0.875000;0.250000;,
  1.000000;0.250000;,
  0.125000;0.375000;,
  0.000000;0.375000;,
  0.250000;0.375000;,
  0.375000;0.375000;,
  0.500000;0.375000;,
  0.625000;0.375000;,
  0.750000;0.375000;,
  0.875000;0.375000;,
  1.000000;0.375000;,
  0.125000;0.500000;,
  0.000000;0.500000;,
  0.250000;0.500000;,
  0.375000;0.500000;,
  0.500000;0.500000;,
  0.625000;0.500000;,
  0.750000;0.500000;,
  0.875000;0.500000;,
  1.000000;0.500000;,
  0.125000;0.625000;,
  0.000000;0.625000;,
  0.250000;0.625000;,
  0.375000;0.625000;,
  0.500000;0.625000;,
  0.625000;0.625000;,
  0.750000;0.625000;,
  0.875000;0.625000;,
  1.000000;0.625000;,
  0.125000;0.750000;,
  0.000000;0.750000;,
  0.250000;0.750000;,
  0.375000;0.750000;,
  0.500000;0.750000;,
  0.625000;0.750000;,
  0.750000;0.750000;,
  0.875000;0.750000;,
  1.000000;0.750000;,
  0.125000;0.875000;,
  0.000000;0.875000;,
  0.250000;0.875000;,
  0.375000;0.875000;,
  0.500000;0.875000;,
  0.625000;0.875000;,
  0.750000;0.875000;,
  0.875000;0.875000;,
  1.000000;0.875000;,
  0.062500;1.000000;,
  0.187500;1.000000;,
  0.312500;1.000000;,
  0.437500;1.000000;,
  0.562500;1.000000;,
  0.687500;1.000000;,
  0.812500;1.000000;,
  0.937500;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.062500;0.000000;,
  0.062500;1.000000;,
  0.000000;1.000000;,
  0.125000;0.000000;,
  0.125000;1.000000;,
  0.187500;0.000000;,
  0.187500;1.000000;,
  0.250000;0.000000;,
  0.250000;1.000000;,
  0.312500;0.000000;,
  0.312500;1.000000;,
  0.375000;0.000000;,
  0.375000;1.000000;,
  0.437500;0.000000;,
  0.437500;1.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.562500;0.000000;,
  0.562500;1.000000;,
  0.625000;0.000000;,
  0.625000;1.000000;,
  0.687500;0.000000;,
  0.687500;1.000000;,
  0.750000;0.000000;,
  0.750000;1.000000;,
  0.812500;0.000000;,
  0.812500;1.000000;,
  0.875000;0.000000;,
  0.875000;1.000000;,
  0.937500;0.000000;,
  0.937500;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.031250;0.000000;,
  0.093750;0.000000;,
  0.156250;0.000000;,
  0.218750;0.000000;,
  0.281250;0.000000;,
  0.343750;0.000000;,
  0.406250;0.000000;,
  0.468750;0.000000;,
  0.531250;0.000000;,
  0.593750;0.000000;,
  0.656250;0.000000;,
  0.718750;0.000000;,
  0.781250;0.000000;,
  0.843750;0.000000;,
  0.906250;0.000000;,
  0.968750;0.000000;,
  0.031250;1.000000;,
  0.093750;1.000000;,
  0.156250;1.000000;,
  0.218750;1.000000;,
  0.281250;1.000000;,
  0.343750;1.000000;,
  0.406250;1.000000;,
  0.468750;1.000000;,
  0.531250;1.000000;,
  0.593750;1.000000;,
  0.656250;1.000000;,
  0.718750;1.000000;,
  0.781250;1.000000;,
  0.843750;1.000000;,
  0.906250;1.000000;,
  0.968750;1.000000;;
 }
}