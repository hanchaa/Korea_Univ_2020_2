library verilog;
use verilog.vl_types.all;
entity forwarding is
    port(
        id_ex_rs1       : in     vl_logic_vector(4 downto 0);
        id_ex_rs2       : in     vl_logic_vector(4 downto 0);
        ex_mem_rd       : in     vl_logic_vector(4 downto 0);
        ex_mem_regwrite : in     vl_logic;
        mem_wb_rd       : in     vl_logic_vector(4 downto 0);
        mem_wb_regwrite : in     vl_logic;
        ex_mem_to_alu_src1: out    vl_logic;
        ex_mem_to_alu_src2: out    vl_logic;
        mem_wb_to_alu_src1: out    vl_logic;
        mem_wb_to_alu_src2: out    vl_logic
    );
end forwarding;
