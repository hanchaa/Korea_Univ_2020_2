library verilog;
use verilog.vl_types.all;
entity hazard_detection is
    port(
        rs1             : in     vl_logic_vector(4 downto 0);
        rs2             : in     vl_logic_vector(4 downto 0);
        id_ex_rd        : in     vl_logic_vector(4 downto 0);
        id_ex_memtoreg  : in     vl_logic;
        branch_taken    : in     vl_logic;
        jal             : in     vl_logic;
        jalr            : in     vl_logic;
        pcwrite         : out    vl_logic;
        if_id_write     : out    vl_logic;
        control_src     : out    vl_logic;
        flush           : out    vl_logic
    );
end hazard_detection;
