// AstroTinker Bot : Task 1C : Pulse Generator and Detector
/*
Instructions
-------------------
Students are not allowed to make any changes in the Module declaration.

This file is used to design a module which will generate a 10us pulse and detect incoming pulse signal.

Recommended Quartus Version : 20.1
The submitted project file must be 20.1 compatible as the evaluation will be done on Quartus Prime Lite 20.1.

Warning: The error due to compatibility will not be entertained.
-------------------
*/

// t1c_pulse_gen_detect
//Inputs : clk_50M, reset, echo_rx
//Output : trigger, distance, pulses, state

// module declaration
module t1c_pulse_gen_detect (
    input clk_50M, reset, echo_rx,
    output reg trigger, out,
    output reg [21:0] pulses,
    output reg [1:0] state
);

initial begin
    trigger = 0; out = 0; pulses = 0; state = 0;
end


//////////////////DO NOT MAKE ANY CHANGES ABOVE THIS LINE//////////////////

reg [21:0] count = 0;

parameter ST_RET=2'b00, ST_WUP=2'b01, ST_TRIG=2'b10, ST_ECHO=2'b11;

always @(posedge clk_50M or posedge reset) begin
    if (reset) begin
        trigger = 0;
        out = 1'b0;
        pulses = 0;
        state = ST_RET;
        count = 0;
    end
    else begin
        count = count + 1;
        case (state)
            ST_RET: begin
                count = 0;
                pulses = 0;
                state = ST_WUP;
					 trigger = 0;
					 pulses =0;
            end

            ST_WUP: begin
                // wait for 1 uS
                if (count == 50) begin
                    state = ST_TRIG;
						  trigger = 1;
                end
            end
            
            ST_TRIG: begin
                // generate 10 us trigger
                if (count == 550) begin
                    state = ST_ECHO;
                    trigger = 0;
						  pulses = 1;
                end
            end

            ST_ECHO: begin
					if(count <= 50549)begin
						if (echo_rx == 1) begin
							pulses = pulses+1;
						end
					end
					else begin
						if(pulses == 29410 ) begin
							out=1;
						end
						state = ST_RET;
					end
					
					
            end

            default: state = ST_RET;
        endcase 
    end
end
//////////////////DO NOT MAKE ANY CHANGES BELOW THIS LINE//////////////////

endmodule
