function startup { wb.centerall; };
function stepforward { wb.stepforward };
function stepbackward { wb.stepbackward };
function walkforward { stop 0; run stepforward, 600 };
function walkbackward { stop 0; run stepbackward, 600 };
function stopwalking { stop 0; wb.centerall };