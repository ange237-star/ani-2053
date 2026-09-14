## ligne de code qui se trouve dans le fichier Nkentseu. qui desactive les tests
 dutc(enable=True)

    dute(enable=True)

## modification de la ligne
 dutc(enable=False)

    dute(enable=False)
## Reveil des tests du module NKMath
 ## Apres avoir taper commande jenga test --project NKMath_Tests --config Debug voici le resultat :
  ## tout les tests on reussit dans le project NKMath_Tests
╔══════════════════════════════════════════════════════════════════════════════════════════════╗
║  Project: NKMath_Tests                                                     Kind: TEST_SUITE  ║
╚══════════════════════════════════════════════════════════════════════════════════════════════╝

ℹ Found 3 source file(s)
✓   [1/3] Compiled: Entry.cpp
✓   [2/3] Compiled: benchmark_smoke.cpp
✓   [3/3] Compiled: test_smoke.cpp
ℹ Linking...
✓ Built: Build\Tests\Debug-Windows\NKMath_Tests.exe

┌──────────────────────────────────────────────────────────────────────────────────────────────┐
│  ✓ Build Successful                                                            Time: 13.57s  │
└──────────────────────────────────────────────────────────────────────────────────────────────┘

════════════════════════════════════════════════════════════════════════════════
                                BUILD COMPLETED
════════════════════════════════════════════════════════════════════════════════
Projects Built:  7/7
Time:           1m6.9s
Status:         ✓ SUCCESS
════════════════════════════════════════════════════════════════════════════════


Running tests for NKMath_Tests...
╔======================================================================╗
║                                                                      ║
║      ██╗   ██╗███╗   ██╗██╗████████╗███████╗███████╗████████╗        ║
║      ██║   ██║████╗  ██║██║╚══██╔══╝██╔════╝██╔════╝╚══██╔══╝        ║
║      ██║   ██║██╔██╗ ██║██║   ██║   █████╗  ███████╗   ██║           ║
║      ██║   ██║██║╚██╗██║██║   ██║   ██╔══╝  ╚════██║   ██║           ║
║      ╚██████╔╝██║ ╚████║██║   ██║   ███████╗███████║   ██║           ║
║       ╚═════╝ ╚═╝  ╚═══╝╚═╝   ╚═╝   ╚══════╝╚══════╝   ╚═╝           ║
║                                                                      ║
║                C++ Unit Testing Framework v1.0.0                     ║
║              Fast, Reliable, and Developer-Friendly                  ║
║                                                                      ║
║  Number of tests: 8                                                  ║
║  Verbose mode: enabled                                               ║
║  Colors: enabled                                                     ║
║  Progress bar: disabled                                              ║
║                                                                      ║
║               Session started: 2026-09-14 07:08:11                   ║
║                                                                      ║
╚======================================================================╝

[INF] C:\Nkentseu\Kernel\Foundation\NKMath\tests\benchmark_smoke.cpp:41 [NKMath Benchmark] NkMath vs std::sin/std::cos
[INF] C:\Nkentseu\Kernel\Foundation\NKMath\tests\benchmark_smoke.cpp:42   NkMath : 33000000.00 ns total (sink=1417.257080)
[INF] C:\Nkentseu\Kernel\Foundation\NKMath\tests\benchmark_smoke.cpp:43   STL    : 22000000.00 ns total (sink=1417.225098)
✓ NKMathBenchmark_TrigonometryLoopVsStd         [OK]  3/3 assertions  (64ms)
  ✓ 3 assertion(s) réussie(s) (moy: 21ms/assert)
✓ NKmathmoke_BitAndIntegerUtilities             [OK]  7/7 assertions  (< 1ms)
  ✓ 7 assertion(s) réussie(s) (moy: < 1ms/assert)
✓ NKmathmoke_DivisionAndInterpolationEdges      [OK]  10/10 assertions  (< 1ms)
  ✓ 10 assertion(s) réussie(s) (moy: < 1ms/assert)
✓ NKmathmoke_QuaternionComposition              [OK]  28/28 assertions  (< 1ms)
  ✓ 28 assertion(s) réussie(s) (moy: < 1ms/assert)
✓ NKmathmoke_QuaternionRotateVector             [OK]  184/184 assertions  (< 1ms)
  ✓ 184 assertion(s) réussie(s) (moy: < 1ms/assert)
✓ NKmathmoke_QuaternionToMatrix                 [OK]  259/259 assertions  (< 1ms)
  ✓ 259 assertion(s) réussie(s) (moy: < 1ms/assert)
✓ NKmathmoke_ScalarFunctions                    [OK]  4/4 assertions  (< 1ms)
  ✓ 4 assertion(s) réussie(s) (moy: < 1ms/assert)
✓ NKmathmoke_VectorAndRectTypes                 [OK]  4/4 assertions  (< 1ms)
  ✓ 4 assertion(s) réussie(s) (moy: < 1ms/assert)


┌────────────────────── RÉSULTATS DES TESTS ──────────────────────┐
│ SUCCÈS                                                          │
├─────────────────────────────────────────────────────────────────┤
│ Tests :      8 réussis, 8 au total          │
│ Assertions : 499 réussies, 499 au total         │
│ Taux succès : Tests: 100.0%, Assertions: 100.0%        │
│ Temps total : 66ms (8ms/test)     │
└──────────────────────────────────────────────────────────────┘

✅ Tous les tests sont réussis !

All tests passed for NKMath_Tests.

## Compter les suites de tests existants
## Apres avoir taper la commande jenga info | Select-Sting "TestSuite" voici la liste de testSuite:
soit 60 TestSuite, 
NKPlatform_Tests             TestSuite     C++        Yes    Yes
NKCore_Tests                 TestSuite     C++        Yes    Yes
NKLogger_Tests               TestSuite     C++        Yes    Yes
NKMath_Tests                 TestSuite     C++        Yes    Yes
NKMemory_Tests               TestSuite     C++        Yes    Yes
NKContainers_Tests           TestSuite     C++        Yes    Yes
NKImage_Tests                TestSuite     C++        Yes    Yes
NKFont_Tests                 TestSuite     C++        Yes    Yes
NKAudio_Tests                TestSuite     C++        Yes    Yes
NKTime_Tests                 TestSuite     C++        Yes    Yes
NKStream_Tests               TestSuite     C++        Yes    Yes
NKThreading_Tests            TestSuite     C++        Yes    Yes
NKFileSystem_Tests           TestSuite     C++        Yes    Yes
NKReflection_Tests           TestSuite     C++        Yes    Yes
NKNetwork_Tests              TestSuite     C++        Yes    Yes
NKSerialization_Tests        TestSuite     C++        Yes    Yes
NKEvent_Tests                TestSuite     C++        Yes    Yes
NKWindow_Tests               TestSuite     C++        Yes    Yes
NKCanvas_Tests               TestSuite     C++        Yes    Yes
NKRHI_Tests                  TestSuite     C++        Yes    Yes
NKUI_Tests                   TestSuite     C++        Yes    Yes
NKCamera_Tests               TestSuite     C++        Yes    Yes
NKCollision_Tests            TestSuite     C++        Yes    Yes
NKPhysics_Tests              TestSuite     C++        Yes    Yes
NKNavigation_Tests           TestSuite     C++        Yes    Yes
NKXR_Tests                   TestSuite     C++        Yes    Yes
RendererRHI_Tests            TestSuite     C++        Yes    Yes
NKRHIDemo_Tests              TestSuite     C++        Yes    Yes
renderdemo_Tests             TestSuite     C++        Yes    Yes
cr2d_Tests                   TestSuite     C++        Yes    Yes
NewGeneration_Tests          TestSuite     C++        Yes    Yes
NkSpriteDemo_Tests           TestSuite     C++        Yes    Yes
NkFontDemo_Tests             TestSuite     C++        Yes    Yes
gltftest_Tests               TestSuite     C++        Yes    Yes
NkDrawableDemo_Tests         TestSuite     C++        Yes    Yes
NkSWRasterPrimitives_Tests   TestSuite     C++        Yes    Yes
NkRHIDemoFull_Tests          TestSuite     C++        Yes    Yes
r2d01_Tests                  TestSuite     C++        Yes    Yes
NkRHIInterpTest_Tests        TestSuite     C++        Yes    Yes
NkRHIDemoFullImage_Tests     TestSuite     C++        Yes    Yes
firsttriangle_Tests          TestSuite     C++        Yes    Yes
NkFDV2_Tests                 TestSuite     C++        Yes    Yes
NkCanvasDemo_Tests           TestSuite     C++        Yes    Yes
Gamepad_Tests                TestSuite     C++        Yes    Yes
NKRenderer_Tests             TestSuite     C++        Yes    Yes
NKTensor_Tests               TestSuite     C++        Yes    Yes
NKAutograd_Tests             TestSuite     C++        Yes    Yes
NKNN_Tests                   TestSuite     C++        Yes    Yes
NKOptim_Tests                TestSuite     C++        Yes    Yes
NKData_Tests                 TestSuite     C++        Yes    Yes
NKTrain_Tests                TestSuite     C++        Yes    Yes
NKInfer_Tests                TestSuite     C++        Yes    Yes
NKRL_Tests                   TestSuite     C++        Yes    Yes
NKAgent_Tests                TestSuite     C++        Yes    Yes
NKEvolve_Tests               TestSuite     C++        Yes    Yes
NKCivilization_Tests         TestSuite     C++        Yes    Yes
NKEmbodied_Tests             TestSuite     C++        Yes    Yes
NKGen_Tests                  TestSuite     C++        Yes    Yes
NKECS_Tests                  TestSuite     C++        Yes    Yes
Noge_Tests                   TestSuite     C++        Yes    Yes
