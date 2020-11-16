//
//  Author: Prof. Taeweon Suh
//          Computer Science & Engineering
//          Korea University
//  Date: July 14, 2020
//  Description: Skeleton design of RV32I Single-cycle CPU
//

`timescale 1ns/1ns
`define simdelay 1

module rv32i_cpu (
		      input         clk, reset,
          output [31:0] pc,		  		// program counter for instruction fetch
          input  [31:0] inst, 			// incoming instruction
          output        Memwrite, 	// 'memory write' control signal
          output [31:0] Memaddr,  	// memory address 
          output [31:0] MemWdata, 	// data to write to memory
          input  [31:0] MemRdata); 	// data read from memory

  wire        auipc, lui;
  wire        alusrc, regwrite;
  wire [4:0]  alucontrol;
  wire        memtoreg, memwrite;
  wire        branch, jal, jalr;

  // **** Juhan Cha: Start ****
  reg [31:0] if_id_inst;
  wire       if_id_write;

  always @(posedge clk)
  begin
    if (reset) if_id_inst <= 32'b0;
    else if (if_id_write) if_id_inst <= #`simdelay inst;
  end

  // Instantiate Controller
  controller i_controller(
    .opcode		(if_id_inst[6:0]), 
		.funct7		(if_id_inst[31:25]), 
		.funct3		(if_id_inst[14:12]), 
  // **** Juhan Cha: Finish ****
		.auipc		(auipc),
		.lui			(lui),
		.memtoreg	(memtoreg),
		.memwrite	(memwrite),
		.branch		(branch),
		.alusrc		(alusrc),
		.regwrite	(regwrite),
		.jal			(jal),
		.jalr			(jalr),
		.alucontrol	(alucontrol));

  // Instantiate Datapath
  datapath i_datapath(
		.clk				(clk),
		.reset			(reset),
		.auipc			(auipc),
		.lui				(lui),
		.memtoreg		(memtoreg),
		.memwrite		(memwrite),
		.branch			(branch),
		.alusrc			(alusrc),
		.regwrite		(regwrite),
		.jal				(jal),
		.jalr				(jalr),
		.alucontrol		(alucontrol),
		.pc				(pc),
		.inst				(if_id_inst), // **** Juhan Cha ****
		.ex_mem_aluout			(Memaddr), // **** Juhan Cha ****
		.ex_mem_MemWdata		(MemWdata), // **** Juhan Cha ****
		.MemRdata		(MemRdata),
    .ex_mem_Memwrite (Memwrite), // **** Juhan Cha ****
    .if_id_write (if_id_write)); // **** Juhan Cha ****


endmodule


//
// Instruction Decoder 
// to generate control signals for datapath
//
module controller(input  [6:0] opcode,
                  input  [6:0] funct7,
                  input  [2:0] funct3,
                  output       auipc,
                  output       lui,
                  output       alusrc,
                  output [4:0] alucontrol,
                  output       branch,
                  output       jal,
                  output       jalr,
                  output       memtoreg,
                  output       memwrite,
                  output       regwrite);

	maindec i_maindec(
		.opcode		(opcode),
		.auipc		(auipc),
		.lui			(lui),
		.memtoreg	(memtoreg),
		.memwrite	(memwrite),
		.branch		(branch),
		.alusrc		(alusrc),
		.regwrite	(regwrite),
		.jal			(jal),
		.jalr			(jalr));

	aludec i_aludec( 
		.opcode     (opcode),
		.funct7     (funct7),
		.funct3     (funct3),
		.alucontrol (alucontrol));


endmodule


//
// RV32I Opcode map = Inst[6:0]
//
`define OP_R			7'b0110011
`define OP_I_Arith	7'b0010011
`define OP_I_Load  	7'b0000011
`define OP_I_JALR  	7'b1100111
`define OP_S			7'b0100011
`define OP_B			7'b1100011
`define OP_U_LUI		7'b0110111
`define OP_J_JAL		7'b1101111

//
// Main decoder generates all control signals except alucontrol 
//
//
module maindec(input  [6:0] opcode,
               output       auipc,
               output       lui,
               output       regwrite,
               output       alusrc,
               output       memtoreg, memwrite,
               output       branch, 
               output       jal,
               output       jalr);

  reg [8:0] controls;

  assign {auipc, lui, regwrite, alusrc, 
			 memtoreg, memwrite, branch, jal, 
			 jalr} = controls;

  always @(*)
  begin
    case(opcode)
      `OP_R: 			controls <= #`simdelay 9'b0010_0000_0; // R-type
      `OP_I_Arith: 	controls <= #`simdelay 9'b0011_0000_0; // I-type Arithmetic
      `OP_I_Load: 	controls <= #`simdelay 9'b0011_1000_0; // I-type Load
      `OP_I_JALR:   controls <= #`simdelay 9'b0011_0000_1; // JALR
      `OP_S: 			controls <= #`simdelay 9'b0001_0100_0; // S-type Store
      `OP_B: 			controls <= #`simdelay 9'b0000_0010_0; // B-type Branch
      `OP_U_LUI: 		controls <= #`simdelay 9'b0111_0000_0; // LUI
      `OP_J_JAL: 		controls <= #`simdelay 9'b0011_0001_0; // JAL
      default:    	controls <= #`simdelay 9'b0000_0000_0; // ???
    endcase
  end

endmodule

//
// ALU decoder generates ALU control signal (alucontrol)
//
module aludec(input      [6:0] opcode,
              input      [6:0] funct7,
              input      [2:0] funct3,
              output reg [4:0] alucontrol);

  always @(*)

    case(opcode)

      `OP_R:   		// R-type
		begin
			case({funct7,funct3})
        10'b0000000_000: alucontrol <= #`simdelay 5'b00000; // addition (add)
        10'b0100000_000: alucontrol <= #`simdelay 5'b10000; // subtraction (sub)
        10'b0000000_111: alucontrol <= #`simdelay 5'b00001; // and (and)
        10'b0000000_110: alucontrol <= #`simdelay 5'b00010; // or (or)
        10'b0000000_100: alucontrol <= #`simdelay 5'b00011; // xor (xor)
        10'b0000000_001: alucontrol <= #`simdelay 5'b00100; // shift left logical (sll)
        default:         alucontrol <= #`simdelay 5'bxxxxx; // ???
      endcase
		end

      `OP_I_Arith:   // I-type Arithmetic
		begin
			case(funct3)
        3'b000: alucontrol <= #`simdelay 5'b00000; // addition (addi)
        3'b111: alucontrol <= #`simdelay 5'b00001; // and (andi)
        3'b110: alucontrol <= #`simdelay 5'b00010; // or (ori)
        3'b100: alucontrol <= #`simdelay 5'b00011; // xor (xori)
        3'b001: alucontrol <= #`simdelay 5'b00100; // shift left logical (slli)
        default: alucontrol <= #`simdelay 5'bxxxxx; // ???
      endcase
		end

      `OP_I_Load: 	// I-type Load (LW, LH, LB...)
      	alucontrol <= #`simdelay 5'b00000;  // addition 

      `OP_I_JALR:   // JALR
        alucontrol <= #`simdelay 5'b00000;  // addition

      `OP_B:   		// B-type Branch (BEQ, BNE, ...)
      	alucontrol <= #`simdelay 5'b10000;  // subtraction 

      `OP_S:   		// S-type Store (SW, SH, SB)
      	alucontrol <= #`simdelay 5'b00000;  // addition 

      `OP_U_LUI: 		// U-type (LUI)
      	alucontrol <= #`simdelay 5'b00000;  // addition

      default: 
      	alucontrol <= #`simdelay 5'b00000;  // 

    endcase
    
endmodule


//
// CPU datapath
//
module datapath(input         clk, reset,
                input  [31:0] inst,
                input         auipc,
                input         lui,
                input         regwrite,
                input         memtoreg,
                input         memwrite,
                input         alusrc, 
                input  [4:0]  alucontrol,
                input         branch,
                input         jal,
                input         jalr,
                output reg [31:0] pc,
                output reg [31:0] ex_mem_aluout, // **** Juhan Cha ****
                output reg [31:0] ex_mem_MemWdata, // **** Juhan Cha ****
                input  [31:0] MemRdata,
                output ex_mem_Memwrite, // **** Juhan Cha ****
                output if_id_write); // **** Juhan Cha ****

  wire [4:0]  rs1, rs2, rd;
  wire [2:0]  funct3;
  wire [31:0] rs1_data, rs2_data;
  reg  [31:0] rd_data;
  wire [20:1] jal_imm;
  wire [31:0] se_jal_imm;
  wire [12:1] br_imm;
  wire [31:0] se_br_imm;
  wire [31:0] se_imm_itype;
  wire [31:0] se_imm_stype;
  wire [31:0] auipc_lui_imm;
  reg  [31:0] alusrc1;
  reg  [31:0] alusrc2;
  wire [31:0] branch_dest, jal_dest;
  wire		  Nflag, Zflag, Cflag, Vflag;
  wire		  f3beq, f3blt, f3bgeu;
  wire		  beq_taken;
  wire		  blt_taken;
  wire      bgeu_taken;

  // **** Juhan Cha: Start ****
  wire [31:0] MemWdata;
  wire [31:0] aluout;
  
  // pipelines for datapath
  reg [31:0] if_id_pc;

  reg [31:0] id_ex_pc;
  reg [4:0]  id_ex_rd;
  reg [4:0]  id_ex_rs1;
  reg [4:0]  id_ex_rs2;
  reg [31:0] id_ex_rs1_data;
  reg [31:0] id_ex_rs2_data;
  reg [31:0] id_ex_se_br_imm;
  reg [31:0] id_ex_se_imm_itype;
  reg [31:0] id_ex_se_imm_stype;
  reg [31:0] id_ex_se_jal_imm;
  reg [31:0] id_ex_auipc_lui_imm;

  reg [31:0] ex_mem_pc;
  reg [31:0] ex_mem_branch_dest;
  reg [31:0] ex_mem_jal_dest;
  reg [4:0]  ex_mem_rd;
  reg [3:0]  ex_mem_NZCV;

  reg [31:0] mem_wb_pc;
  reg [4:0]  mem_wb_rd;
  reg [31:0] mem_wb_aluout;
  reg [31:0] mem_wb_MemRdata;

  // pipelines for control signals
  reg [4:0] id_ex_alucontrol;
  reg [11:0] id_ex_controls;
  reg [8:0] ex_mem_controls;
  reg [3:0] mem_wb_controls;

  // wires for forwarding unit
  wire ex_mem_to_alu_src1, ex_mem_to_alu_src2, mem_wb_to_alu_src1, mem_wb_to_alu_src2;
  reg [31:0] after_forward_rs1, after_forward_rs2;
  wire rd_to_rs1, rd_to_rs2;
  wire pcwrite, control_src;

  always @(posedge clk)
  begin
    if (reset) 
    begin
      if_id_pc <= 32'b0;

      id_ex_pc <= 32'b0;
      id_ex_rd <= 5'b0;
      id_ex_rs1 <= 5'b0;
      id_ex_rs2 <= 5'b0;
      id_ex_rs1_data <= 32'b0;
      id_ex_rs2_data <= 32'b0;
      id_ex_se_br_imm <= 32'b0;
      id_ex_se_imm_itype <= 32'b0;
      id_ex_se_imm_stype <= 32'b0;
      id_ex_se_jal_imm <= 32'b0;
      id_ex_auipc_lui_imm <= 32'b0;
      
      ex_mem_pc <= 32'b0;
      ex_mem_branch_dest <= 32'b0;
      ex_mem_jal_dest <= 32'b0;
      ex_mem_rd <= 5'b0;
      ex_mem_MemWdata <= 32'b0;
      ex_mem_aluout <= 32'b0;
      ex_mem_NZCV <= 4'b0;
      
      mem_wb_pc <= 32'b0;
      mem_wb_rd <= 5'b0;
      mem_wb_aluout <= 32'b0;
      mem_wb_MemRdata <= 32'b0;

      id_ex_alucontrol <= 5'b0;
      id_ex_controls <= 12'b0;
      ex_mem_controls <= 9'b0;
      mem_wb_controls <= 4'b0;
    end
    
    else
    begin
      if (if_id_write) if_id_pc <= #`simdelay pc;

      id_ex_pc <= #`simdelay if_id_pc;
      id_ex_rd <= #`simdelay rd;
      id_ex_rs1 <= #`simdelay rs1;
      id_ex_rs2 <= #`simdelay rs2;
      if (rd_to_rs1) id_ex_rs1_data <= #`simdelay rd_data;
      else id_ex_rs1_data <= #`simdelay rs1_data;
      if (rd_to_rs2) id_ex_rs2_data <= #`simdelay rd_data;
      else id_ex_rs2_data <= #`simdelay rs2_data;
      id_ex_se_br_imm <= #`simdelay se_br_imm;
      id_ex_se_imm_itype <= #`simdelay se_imm_itype;
      id_ex_se_imm_stype <= #`simdelay se_imm_stype;
      id_ex_se_jal_imm <= #`simdelay se_jal_imm;
      id_ex_auipc_lui_imm <= #`simdelay auipc_lui_imm;

      ex_mem_pc <= #`simdelay id_ex_pc;
      ex_mem_branch_dest <= #`simdelay branch_dest;
      ex_mem_jal_dest <= #`simdelay jal_dest;
      ex_mem_rd <= #`simdelay id_ex_rd;
      ex_mem_MemWdata <= #`simdelay after_forward_rs2;
      ex_mem_aluout <= #`simdelay aluout;
      ex_mem_NZCV <= #`simdelay {Nflag, Zflag, Cflag, Vflag};

      mem_wb_pc <= #`simdelay ex_mem_pc;
      mem_wb_rd <= #`simdelay ex_mem_rd;
      mem_wb_aluout <= #`simdelay ex_mem_aluout;
      mem_wb_MemRdata <= #`simdelay MemRdata;
      
      id_ex_alucontrol <= #`simdelay alucontrol;
      if (control_src) id_ex_controls <= 12'b0;
      else id_ex_controls <= #`simdelay {auipc, lui, alusrc, memwrite, branch, f3beq, f3blt, f3bgeu, jal, jalr, memtoreg, regwrite};
      ex_mem_controls <= #`simdelay id_ex_controls[8:0];
      mem_wb_controls <= #`simdelay ex_mem_controls[3:0];
    end
  end

  assign ex_mem_Memwrite = ex_mem_controls[8];
  // **** Juhan Cha: Finish ****

  assign rs1 = inst[19:15];
  assign rs2 = inst[24:20];
  assign rd  = inst[11:7];
  assign funct3  = inst[14:12];

  //
  // PC (Program Counter) logic 
  //
  assign f3beq  = (funct3 == 3'b000);
  assign f3blt  = (funct3 == 3'b100);
  assign f3bgeu = (funct3 == 3'b111);

  assign beq_taken  =  ex_mem_controls[7] & ex_mem_controls[6] & ex_mem_NZCV[2];
  assign blt_taken  =  ex_mem_controls[7] & ex_mem_controls[5] & (ex_mem_NZCV[3] != ex_mem_NZCV[2]);
  assign bgeu_taken =  ex_mem_controls[7] & ex_mem_controls[4] & ex_mem_NZCV[1];

  // **** Juhan Cha: Start ****
  assign branch_dest = (id_ex_pc + id_ex_se_br_imm);
  assign jal_dest 	= (id_ex_pc + id_ex_se_jal_imm);

  always @(posedge clk, posedge reset)
  begin
    if (reset)  pc <= 32'b0;
	  else if (pcwrite)
	  begin
	    if (beq_taken | blt_taken | bgeu_taken) // branch_taken
				pc <= #`simdelay ex_mem_branch_dest;
		  else if (ex_mem_controls[3]) // jal
				pc <= #`simdelay ex_mem_jal_dest;
      else if (ex_mem_controls[2])
        pc <= #`simdelay ex_mem_aluout;
  // **** Juhan Cha: Finish ****
		  else 
				pc <= #`simdelay (pc + 4);
	  end
  end


  // JAL immediate
  assign jal_imm[20:1] = {inst[31],inst[19:12],inst[20],inst[30:21]};
  assign se_jal_imm[31:0] = {{11{jal_imm[20]}},jal_imm[20:1],1'b0};

  // Branch immediate
  assign br_imm[12:1] = {inst[31],inst[7],inst[30:25],inst[11:8]};
  assign se_br_imm[31:0] = {{19{br_imm[12]}},br_imm[12:1],1'b0};



  // 
  // Register File 
  //
  regfile i_regfile(
    .clk			(clk),
    .we			(mem_wb_controls[0]), // **** Juhan Cha ****
    .rs1			(rs1),
    .rs2			(rs2),
    .rd			(mem_wb_rd), // **** Juhan Cha ****
    .rd_data	(rd_data),
    .rs1_data	(rs1_data),
    .rs2_data	(rs2_data));


	//
	// ALU 
	//
	alu i_alu(
		.a			(alusrc1),
		.b			(alusrc2),
		.alucont	(id_ex_alucontrol), // **** Juhan Cha ****
		.result	(aluout),
		.N			(Nflag),
		.Z			(Zflag),
		.C			(Cflag),
		.V			(Vflag));

  // **** Juhan Cha: Start ****
  hazard_detection i_hazard_detection(
    .rs1 (rs1),
    .rs2 (rs2),
    .id_ex_rd (id_ex_rd),
    .id_ex_memtoreg (id_ex_controls[1]),
    .pcwrite (pcwrite),
    .if_id_write (if_id_write),
    .control_src (control_src));

  forwardingWBtoD i_forwardingWBtoD(
    .rs1 (rs1),
    .rs2 (rs2),
    .mem_wb_rd (mem_wb_rd),
    .mem_wb_regwrite (mem_wb_controls[0]),
    .rd_to_rs1 (rd_to_rs1),
    .rd_to_rs2 (rd_to_rs2));

  forwarding i_forwarding(
    .id_ex_rs1 (id_ex_rs1),
    .id_ex_rs2 (id_ex_rs2),
    .ex_mem_rd (ex_mem_rd),
    .ex_mem_regwrite (ex_mem_controls[0]),
    .mem_wb_rd (mem_wb_rd),
    .mem_wb_regwrite (mem_wb_controls[0]),
    .ex_mem_to_alu_src1 (ex_mem_to_alu_src1),
    .ex_mem_to_alu_src2 (ex_mem_to_alu_src2),
    .mem_wb_to_alu_src1 (mem_wb_to_alu_src1),
    .mem_wb_to_alu_src2 (mem_wb_to_alu_src2));
  
  always @(*)
  begin
    if (ex_mem_to_alu_src1) after_forward_rs1[31:0] = ex_mem_aluout[31:0];
    else if (mem_wb_to_alu_src1) after_forward_rs1[31:0] = rd_data[31:0];
    else after_forward_rs1[31:0] = id_ex_rs1_data[31:0];
  end

  always @(*)
  begin
    if (ex_mem_to_alu_src2) after_forward_rs2[31:0] = ex_mem_aluout[31:0];
    else if (mem_wb_to_alu_src2) after_forward_rs2[31:0] = rd_data[31:0];
    else after_forward_rs2[31:0] = id_ex_rs2_data[31:0];
  end

	// 1st source to ALU (alusrc1)
	always@(*)
	begin
		if      (id_ex_controls[11])	alusrc1[31:0] = id_ex_pc[31:0];
		else if (id_ex_controls[10]) 	alusrc1[31:0] = 32'b0;
		else          	              alusrc1[31:0] = after_forward_rs1[31:0];
	end
	
	// 2nd source to ALU (alusrc2)
	always@(*)
	begin
		if	    (id_ex_controls[11] | id_ex_controls[10])   alusrc2[31:0] = id_ex_auipc_lui_imm[31:0];
		else if (id_ex_controls[9] & id_ex_controls[8])     alusrc2[31:0] = id_ex_se_imm_stype[31:0];
		else if (id_ex_controls[9])                         alusrc2[31:0] = id_ex_se_imm_itype[31:0];
		else                                                alusrc2[31:0] = after_forward_rs2[31:0];
	end
  // **** Juhan Cha: Finish ****
	
	assign se_imm_itype[31:0] = {{20{inst[31]}},inst[31:20]};
	assign se_imm_stype[31:0] = {{20{inst[31]}},inst[31:25],inst[11:7]};
	assign auipc_lui_imm[31:0] = {inst[31:12],12'b0};


  // **** Juhan Cha: Start ****
	// Data selection for writing to RF
	always@(*)
	begin
		if	    (mem_wb_controls[3] | mem_wb_controls[2])			rd_data[31:0] = mem_wb_pc[31:0] + 32'b0100;
		else if (mem_wb_controls[1])	                        rd_data[31:0] = mem_wb_MemRdata[31:0];
		else                                      						rd_data[31:0] = mem_wb_aluout[31:0];
	end
  // **** Juhan Cha: Finish ****
	
endmodule
