library verilog;
use verilog.vl_types.all;
entity maindec is
    port(
        opcode          : in     vl_logic_vector(6 downto 0);
        auipc           : out    vl_logic;
        lui             : out    vl_logic;
        regwrite        : out    vl_logic;
        alusrc          : out    vl_logic;
        memtoreg        : out    vl_logic;
        memwrite        : out    vl_logic;
        branch          : out    vl_logic;
        jal             : out    vl_logic;
        jalr            : out    vl_logic
    );
end maindec;
