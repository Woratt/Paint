cd build

cd tests

./test_paint

LLVM_PROFILE_FILE="coverage.profraw" ./test_paint

llvm-profdata merge -sparse coverage.profraw -o coverage.profdata

llvm-cov report ./test_paint -instr-profile=coverage.profdata

llvm-cov report ./test_paint -instr-profile=coverage.profdata \
    -ignore-filename-regex=".*googletest.*|.*test_.*|.*moc_.*|.*qrc_.*|.*CMakeFiles.*"

llvm-cov show ./test_paint -instr-profile=coverage.profdata \
    -ignore-filename-regex=".*googletest.*|.*test_.*|.*moc_.*|.*qrc_.*|.*CMakeFiles.*" \
    --format=html -output-dir=coverage_report

cd tests
cd coverage_report
open index.html
