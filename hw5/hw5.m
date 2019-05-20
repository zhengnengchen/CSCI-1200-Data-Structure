freights = randi(14, [1, 6]) * 5 + 30;
engines = 2;
poss = [];
for i = 1:engines
    comb = nchoosek(freights, 4 - i);
    comb = [comb, zeros(length(comb), i - 1)];
    poss = [poss;comb(sum(comb, 2) < 318.75 * i, :)];
end