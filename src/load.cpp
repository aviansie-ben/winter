#include "wabt/src/binary-reader.h"
#include "wabt/src/binary-reader-nop.h"

#include "module.hpp"
#include "opcode.hpp"
#include "type.hpp"

using wabt::Address;
using wabt::Index;
using wabt::Limits;
using wabt::Result;
using wabt::string_view;

namespace winter {

class BinaryReader : public wabt::BinaryReaderNop {
    AbstractModule* _module;
    std::vector<FuncSig> _types;

    InstructionStreamBuilder _instrs;

public:
    BinaryReader(AbstractModule* module) : _module(module) {}

    ValueType MapType(wabt::Type t);

    virtual Result OnType(Index index, Index param_count, wabt::Type* param_types, Index result_count, wabt::Type* result_types);

    virtual Result OnImportFunc(Index import_index, string_view module_name, string_view field_name, Index func_index, Index sig_index) { WASSERT(false, "Not yet implemented: OnImportFunc"); }
    virtual Result OnImportTable(Index import_index, string_view module_name, string_view field_name, Index table_index, wabt::Type elem_type, const Limits* elem_limits) { WASSERT(false, "Not yet implemented: OnImportTable"); }
    virtual Result OnImportMemory(Index import_index, string_view module_name, string_view field_name, Index memory_index, const Limits* page_limits) { WASSERT(false, "Not yet implemented: OnImportMemory"); }
    virtual Result OnImportGlobal(Index import_index, string_view module_name, string_view field_name, Index global_index, wabt::Type type, bool mutable_) { WASSERT(false, "Not yet implemented: OnImportGlobal"); }
    virtual Result OnImportEvent(Index import_index, string_view module_name, string_view field_name, Index event_index, Index sig_index) { { WASSERT(false, "Not yet implemented: OnImportEvent"); } }

    virtual Result OnFunction(Index index, Index sig_index);
    virtual Result OnTable(Index index, wabt::Type elem_type, const Limits* elem_limits) { WASSERT(false, "Not yet implemented: OnTable"); }
    virtual Result OnMemory(Index index, const Limits* limits) { WASSERT(false, "Not yet implemented: OnMemory"); }

    virtual Result BeginGlobal(Index index, wabt::Type type, bool mutable_) { WASSERT(false, "Not yet implemented: BeginGlobal"); }
    virtual Result BeginGlobalInitExpr(Index index) { WASSERT(false, "Not yet implemented: BeginGlobalInitExpr"); }
    virtual Result EndGlobalInitExpr(Index index) { WASSERT(false, "Not yet implemented: EndGlobalInitExpr"); }
    virtual Result EndGlobal(Index index) { WASSERT(false, "Not yet implemented: EndGlobal"); }

    virtual Result OnExport(Index index, wabt::ExternalKind kind, Index item_index, string_view name);

    virtual Result OnStartFunction(Index func_index) { WASSERT(false, "Not yet implemented: OnStartFunction"); }

    virtual Result OnLocalDecl(Index decl_index, Index count, wabt::Type type) { WASSERT(false, "Not yet implemented: OnLocalDecl"); }

    virtual Result OnOpcode(wabt::Opcode opcode);
    virtual Result OnAtomicLoadExpr(wabt::Opcode opcode, uint32_t alignment_log2, Address offset) { WASSERT(false, "Not yet implemented: OnAtomicLoadExpr"); }
    virtual Result OnAtomicStoreExpr(wabt::Opcode opcode, uint32_t alignment_log2, Address offset) { WASSERT(false, "Not yet implemented: OnAtomicStoreExpr"); }
    virtual Result OnAtomicRmwExpr(wabt::Opcode opcode, uint32_t alignment_log2, Address offset) { WASSERT(false, "Not yet implemented: OnAtomicRmwExpr"); }
    virtual Result OnAtomicRmwCmpxchgExpr(wabt::Opcode opcode, uint32_t alignment_log2, Address offset) { WASSERT(false, "Not yet implemented: OnAtomicRmwCmpxchgExpr"); }
    virtual Result OnAtomicWaitExpr(wabt::Opcode opcode, uint32_t alignment_log2, Address offset) { WASSERT(false, "Not yet implemented: OnAtomicWaitExpr"); }
    virtual Result OnAtomicNotifyExpr(wabt::Opcode opcode, uint32_t alignment_log2, Address offset) { WASSERT(false, "Not yet implemented: OnAtomicNotifyExpr"); }
    virtual Result OnBinaryExpr(wabt::Opcode opcode) { WASSERT(false, "Not yet implemented: OnBinaryExpr"); }
    virtual Result OnBlockExpr(wabt::Type sig_type) { WASSERT(false, "Not yet implemented: OnBlockExpr"); }
    virtual Result OnBrExpr(Index depth) { WASSERT(false, "Not yet implemented: OnBrExpr"); }
    virtual Result OnBrIfExpr(Index depth) { WASSERT(false, "Not yet implemented: OnBrIfExpr"); }
    virtual Result OnBrOnExnExpr(Index depth, Index event_index) { WASSERT(false, "Not yet implemented: OnBrOnExnExpr"); }
    virtual Result OnBrTableExpr(Index num_targets, Index* target_depths, Index default_target_depth) { WASSERT(false, "Not yet implemented: OnBrTableExpr"); }
    virtual Result OnCallExpr(Index func_index) { WASSERT(false, "Not yet implemented: OnCallExpr"); }
    virtual Result OnCallIndirectExpr(Index sig_index, Index table_index) { WASSERT(false, "Not yet implemented: OnCallIndirectExpr"); }
    virtual Result OnCatchExpr() { WASSERT(false, "Not yet implemented: OnCatchExpr"); }
    virtual Result OnCompareExpr(wabt::Opcode opcode) { WASSERT(false, "Not yet implemented: OnCompareExpr"); }
    virtual Result OnConvertExpr(wabt::Opcode opcode) { WASSERT(false, "Not yet implemented: OnConvertExpr"); }
    virtual Result OnDropExpr() { WASSERT(false, "Not yet implemented: OnDropExpr"); }
    virtual Result OnElseExpr() { WASSERT(false, "Not yet implemented: OnElseExpr"); }
    virtual Result OnEndExpr() { WASSERT(false, "Not yet implemented: OnEndExpr"); }
    virtual Result OnEndFunc() { return Result::Ok; }
    virtual Result OnF32ConstExpr(uint32_t value_bits) { WASSERT(false, "Not yet implemented: OnF32ConstExpr"); }
    virtual Result OnF64ConstExpr(uint64_t value_bits) { WASSERT(false, "Not yet implemented: OnF64ConstExpr"); }
    virtual Result OnV128ConstExpr(v128 value_bits) { WASSERT(false, "Not yet implemented: OnV128ConstExpr"); }
    virtual Result OnGlobalGetExpr(Index global_index) { WASSERT(false, "Not yet implemented: OnGlobalGetExpr"); }
    virtual Result OnGlobalSetExpr(Index global_index) { WASSERT(false, "Not yet implemented: OnGlobalSetExpr"); }
    virtual Result OnI32ConstExpr(uint32_t value);
    virtual Result OnI64ConstExpr(uint64_t value) { WASSERT(false, "Not yet implemented: OnI64ConstExpr"); }
    virtual Result OnIfExpr(wabt::Type sig_type) { WASSERT(false, "Not yet implemented: OnIfExpr"); }
    virtual Result OnLoadExpr(wabt::Opcode opcode, uint32_t alignment_log2, Address offset) { WASSERT(false, "Not yet implemented: OnLoadExpr"); }
    virtual Result OnLocalGetExpr(Index local_index) { WASSERT(false, "Not yet implemented: OnLocalGetExpr"); }
    virtual Result OnLocalSetExpr(Index local_index) { WASSERT(false, "Not yet implemented: OnLocalSetExpr"); }
    virtual Result OnLocalTeeExpr(Index local_index) { WASSERT(false, "Not yet implemented: OnLocalTeeExpr"); }
    virtual Result OnLoopExpr(wabt::Type sig_type) { WASSERT(false, "Not yet implemented: OnLoopExpr"); }
    virtual Result OnMemoryCopyExpr() { WASSERT(false, "Not yet implemented: OnMemoryCopyExpr"); }
    virtual Result OnDataDropExpr(Index segment_index) { WASSERT(false, "Not yet implemented: OnDataDropExpr"); }
    virtual Result OnMemoryFillExpr() { WASSERT(false, "Not yet implemented: OnMemoryFillExpr"); }
    virtual Result OnMemoryGrowExpr() { WASSERT(false, "Not yet implemented: OnMemoryGrowExpr"); }
    virtual Result OnMemoryInitExpr(Index segment_index) { WASSERT(false, "Not yet implemented: OnMemoryInitExpr"); }
    virtual Result OnMemorySizeExpr() { WASSERT(false, "Not yet implemented: OnMemorySizeExpr"); }
    virtual Result OnTableCopyExpr() { WASSERT(false, "Not yet implemented: OnTableCopyExpr"); }
    virtual Result OnElemDropExpr(Index segment_index) { WASSERT(false, "Not yet implemented: OnElemDropExpr"); }
    virtual Result OnTableInitExpr(Index segment_index) { WASSERT(false, "Not yet implemented: OnTableInitExpr"); }
    virtual Result OnTableGetExpr(Index table_index) { WASSERT(false, "Not yet implemented: OnTableGetExpr"); }
    virtual Result OnTableSetExpr(Index table_index) { WASSERT(false, "Not yet implemented: OnTableSetExpr"); }
    virtual Result OnTableGrowExpr(Index table_index) { WASSERT(false, "Not yet implemented: OnTableGrowExpr"); }
    virtual Result OnTableSizeExpr(Index table_index) { WASSERT(false, "Not yet implemented: OnTableSizeExpr"); }
    virtual Result OnRefNullExpr() { WASSERT(false, "Not yet implemented: OnRefNullExpr"); }
    virtual Result OnRefIsNullExpr() { WASSERT(false, "Not yet implemented: OnRefIsNullExpr"); }
    virtual Result OnNopExpr() { WASSERT(false, "Not yet implemented: OnNopExpr"); }
    virtual Result OnRethrowExpr() { WASSERT(false, "Not yet implemented: OnRethrowExpr"); }
    virtual Result OnReturnExpr() { return Result::Ok; }
    virtual Result OnReturnCallExpr(Index func_index) { WASSERT(false, "Not yet implemented: OnReturnCallExpr"); }
    virtual Result OnReturnCallIndirectExpr(Index sig_index, Index table_index) { WASSERT(false, "Not yet implemented: OnReturnCallIndirectExpr"); }
    virtual Result OnSelectExpr() { WASSERT(false, "Not yet implemented: OnSelectExpr"); }
    virtual Result OnStoreExpr(wabt::Opcode opcode, uint32_t alignment_log2, Address offset) { WASSERT(false, "Not yet implemented: OnStoreExpr"); }
    virtual Result OnThrowExpr(Index event_index) { WASSERT(false, "Not yet implemented: OnThrowExpr"); }
    virtual Result OnTryExpr(wabt::Type sig_type) { WASSERT(false, "Not yet implemented: OnTryExpr"); }
    virtual Result OnUnaryExpr(wabt::Opcode opcode) { WASSERT(false, "Not yet implemented: OnUnaryExpr"); }
    virtual Result OnTernaryExpr(wabt::Opcode opcode) { WASSERT(false, "Not yet implemented: OnTernaryExpr"); }
    virtual Result OnUnreachableExpr() { WASSERT(false, "Not yet implemented: OnUnreachableExpr"); }
    virtual Result OnSimdLaneOpExpr(wabt::Opcode opcode, uint64_t value) { WASSERT(false, "Not yet implemented: OnSimdLaneOpExpr"); }
    virtual Result OnSimdShuffleOpExpr(wabt::Opcode opcode, v128 value) { WASSERT(false, "Not yet implemented: OnSimdShuffleOpExpr"); }

    virtual Result EndFunctionBody(Index index);

    virtual Result BeginElemSegment(Index index) { WASSERT(false, "Not yet implemented: BeginElemSegment"); }
    virtual Result BeginElemSegmentInitExpr(Index index) { WASSERT(false, "Not yet implemented: BeginElemSegmentInitExpr"); }
    virtual Result EndElemSegmentInitExpr(Index index) { WASSERT(false, "Not yet implemented: EndElemSegmentInitExpr"); }
    virtual Result EndElemSegment() { WASSERT(false, "Not yet implemented: EndElemSegment"); }
    virtual Result OnElemSegmentFunctionIndex(Index segment_index, Index func_index) { WASSERT(false, "Not yet implemented: EndElemSegmentFunctionIndex"); }

    virtual Result BeginDataSegment(Index index, Index memory_index, bool passive) { WASSERT(false, "Not yet implemented: BeginDataSegment"); }
    virtual Result BeginDataSegmentInitExpr(Index index) { WASSERT(false, "Not yet implemented: BeginDataSegmentInitExpr"); }
    virtual Result EndDataSegmentInitExpr(Index index) { WASSERT(false, "Not yet implemented: EndDataSegmentInitExpr"); }
    virtual Result OnDataSegmentData(Index index, const void* data, Address size) { WASSERT(false, "Not yet implemented: OnDataSegmentData"); }
    virtual Result EndDataSegment(Index index) { WASSERT(false, "Not yet implemented: EndDataSegment"); }

    virtual Result OnDataCount(Index count) { WASSERT(false, "Not yet implemented: OnDataCount"); }

    virtual Result OnModuleName(string_view name) {}
    virtual Result OnFunctionName(Index function_index, string_view function_name) {}
    virtual Result OnLocalName(Index function_index, Index local_index, string_view local_name) {}

    virtual Result OnEventType(Index index, Index sig_index) { WASSERT(false, "Not yet implemented: OnEventType"); }

    virtual Result OnInitExprF32ConstExpr(Index index, uint32_t value) { WASSERT(false, "Not yet implemented: OnInitExprF32ConstExpr"); }
    virtual Result OnInitExprF64ConstExpr(Index index, uint64_t value) { WASSERT(false, "Not yet implemented: OnInitExprF64ConstExpr"); }
    virtual Result OnInitExprV128ConstExpr(Index index, v128 value) { WASSERT(false, "Not yet implemented: OnInitExprV128ConstExpr"); }
    virtual Result OnInitExprGlobalGetExpr(Index index, Index global_index) { WASSERT(false, "Not yet implemented: OnInitExprGlobalGetExpr"); }
    virtual Result OnInitExprI32ConstExpr(Index index, uint32_t value) { WASSERT(false, "Not yet implemented: OnInitExprI32ConstExpr"); }
    virtual Result OnInitExprI64ConstExpr(Index index, uint64_t value) { WASSERT(false, "Not yet implemented: OnInitExprI64ConstExpr"); }
};

ValueType BinaryReader::MapType(wabt::Type t) {
    switch (t) {
        case wabt::Type::I32:
            return ValueType::i32();
        case wabt::Type::I64:
            return ValueType::i64();
        case wabt::Type::F32:
            return ValueType::f32();
        case wabt::Type::F64:
            return ValueType::f64();
        default:
            WASSERT(false, "Unsupported type %u", static_cast<uint32_t>(t));
    }
}

Result BinaryReader::OnType(Index index, Index param_count, wabt::Type* param_types, Index result_count, wabt::Type* result_types) {
    std::vector<ValueType> winter_param_types;
    std::vector<ValueType> winter_result_types;

    for (Index i = 0; i < param_count; i++)
        winter_param_types.push_back(MapType(param_types[i]));

    for (Index i = 0; i < result_count; i++)
        winter_result_types.push_back(MapType(result_types[i]));

    _types.push_back(FuncSig(winter_result_types, winter_param_types));
    return Result::Ok;
}

Result BinaryReader::OnFunction(Index index, Index sig_index) {
    // TODO Check bounds
    WASSERT(index == _module->funcs().size(), "Wrong function index");
    _module->funcs().push_back(AbstractFunc(false, "", nullptr, _types.at(sig_index)));
    return Result::Ok;
}

static ExportType MapExportType(wabt::ExternalKind kind) {
    switch (kind) {
        case wabt::ExternalKind::Func:
            return ExportType::Func;
        default:
            WASSERT(false, "Unsupported external kind %u", static_cast<uint32_t>(kind));
    }
}

Result BinaryReader::OnExport(Index index, wabt::ExternalKind kind, Index item_index, string_view name) {
    _module->exports().push_back(Export(name.to_string(), MapExportType(kind), item_index));
    return Result::Ok;
}

static std::unordered_map<uint32_t, OpcodeValue> opcodeMap = {
    { wabt::Opcode::I32Const, OpcodeValue::I32Const },
    { wabt::Opcode::Return, OpcodeValue::Return }
};

static OpcodeValue MapOpcode(wabt::Opcode opcode) {
    auto it = opcodeMap.find(static_cast<uint32_t>(static_cast<wabt::Opcode::Enum>(opcode)));
    WASSERT(it != opcodeMap.end(), "Unhandled opcode %s", opcode.GetName());

    return it->second;
}

Result BinaryReader::OnOpcode(wabt::Opcode opcode) {
    if (opcode == wabt::Opcode::End) return Result::Ok;

    _instrs.write_opcode(MapOpcode(opcode));
    return Result::Ok;
}

Result BinaryReader::OnI32ConstExpr(uint32_t value) {
    _instrs.write_u32(value);
    return Result::Ok;
}

Result BinaryReader::EndFunctionBody(Index index) {
    _module->funcs().at(index).instrs = std::make_shared<InstructionStream>(_instrs.finish());
    return Result::Ok;
}

AbstractModule AbstractModule::parse(const void* data, size_t size) {
    wabt::ReadBinaryOptions options;
    options.read_debug_names = true;

    AbstractModule module;
    BinaryReader reader(&module);

    Result result = ReadBinary(data, size, &reader, options);
    if (result != Result::Ok)
        throw result; // TODO Throw a better error

    return module;
}

}
