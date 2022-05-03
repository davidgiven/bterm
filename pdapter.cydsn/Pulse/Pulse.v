
//`#start header` -- edit after this line, do not edit this line
// ========================================
//
// Copyright YOUR COMPANY, THE YEAR
// All Rights Reserved
// UNPUBLISHED, LICENSED SOFTWARE.
//
// CONFIDENTIAL AND PROPRIETARY INFORMATION
// WHICH IS THE PROPERTY OF your company.
//
// ========================================
`include "cypress.v"
//`#end` -- edit above this line, do not edit this line
// Generated on 04/27/2022 at 23:04
// Component: Pulse
module Pulse (
	output  pulse,
	input   clock,
	input   trigger
);

//`#start body` -- edit after this line, do not edit this line

reg oldtrigger;
reg d0;
reg d1;
reg d2;

assign pulse = d0 | d1 | d2;

always @(posedge clock)
begin
    if (trigger && !oldtrigger)
    begin
        d0 <= 1;
        d1 <= 1;
        d2 <= 1;
    end
    else
    begin
        d2 <= d1;
        d1 <= d0;
        d0 <= 0;
    end
    
    oldtrigger <= trigger;
end

//        Your code goes here

//`#end` -- edit above this line, do not edit this line
endmodule
//`#start footer` -- edit after this line, do not edit this line
//`#end` -- edit above this line, do not edit this line
