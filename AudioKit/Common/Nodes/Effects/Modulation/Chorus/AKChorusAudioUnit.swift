// Copyright AudioKit. All Rights Reserved. Revision History at http://github.com/AudioKit/AudioKit/

import AVFoundation

public class AKChorusAudioUnit: AKAudioUnitBase {

    let frequency = AUParameter(
        identifier: "frequency",
        name: "Frequency (Hz)",
        address: AKModulatedDelayParameter.frequency.rawValue,
        range: AKChorus.frequencyRange,
        unit: .hertz,
        flags: .default)

    let depth = AUParameter(
        identifier: "depth",
        name: "Depth 0-1",
        address: AKModulatedDelayParameter.depth.rawValue,
        range: AKChorus.depthRange,
        unit: .generic,
        flags: .default)

    let feedback = AUParameter(
        identifier: "feedback",
        name: "Feedback 0-1",
        address: AKModulatedDelayParameter.feedback.rawValue,
        range: AKChorus.feedbackRange,
        unit: .generic,
        flags: .default)

    let dryWetMix = AUParameter(
        identifier: "dryWetMix",
        name: "Dry Wet Mix 0-1",
        address: AKModulatedDelayParameter.dryWetMix.rawValue,
        range: AKChorus.dryWetMixRange,
        unit: .generic,
        flags: .default)

    public override func createDSP() -> AKDSPRef {
        return createChorusDSP()
    }

    public override init(componentDescription: AudioComponentDescription,
                  options: AudioComponentInstantiationOptions = []) throws {
        try super.init(componentDescription: componentDescription, options: options)

        parameterTree = AUParameterTree.createTree(withChildren: [frequency, depth, feedback, dryWetMix])
    }
}
