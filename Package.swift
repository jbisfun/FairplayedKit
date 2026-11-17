// swift-tools-version: 5.9
import PackageDescription

let package = Package(
    name: "FairplayedKit",
    platforms: [.iOS(.v16)],
    products: [
        .library(name: "FairplayedKit", targets: ["FairplayedKit"]),
    ],
    targets: [
        .target(
            name: "FairplayedKit",
            linkerSettings: [.linkedLibrary("z")]
        ),
    ]
)
