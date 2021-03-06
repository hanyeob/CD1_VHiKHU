% DFT321 on Nx3 arrays
% also returns freq. domain data
function [out, freq] = dft321(in, filt)

    % unity-gain first-order high-pass filter
    a = [.02-1 0];
    b = [1 .02-1];

    if nargin > 1 && filt
        A = fft(filtfilt(b, a, in));
    else
        A = fft(bsxfun(@minus, in, mean(in)));
    end
    A_s = sqrt(sum(A .* conj(A), 2));
    theta = angle(sum(A,2));
    
    out = real(ifft(A_s .* exp(1j * theta)));
    freq = A_s(1:floor(end/2));

end