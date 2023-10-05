(function () {
  document.addEventListener("DOMContentLoaded", function () {
    const closeSvg =
      "PHN2ZyB3aWR0aD0iMTYiIGhlaWdodD0iMTUiIGZpbGw9Im5vbmUiIHhtbG5zPSJodHRwOi8vd3d3LnczLm9yZy8yMDAwL3N2ZyI+PHBhdGggZD0iTTMuNzUuMzMzIDEgNC4xOTNsNS4yNSAzLjYwMiA2IDcuMjA1TDE0IDExLjY1NWwtMy0zLjA4OC01LjI1LTUuNDA0LTItMi44M1oiIGZpbGw9IiNmZmYiLz48cGF0aCBkPSJNMTUuMDI1IDMuNDc2IDExLjI3LjYyNiA4LjIyIDUuOTIybC02LjQ0MyA2LjI4NyAyLjkyMSAyLjU3NiAzLjE0NS00LjI2NCA0Ljc3NS01LjQzMiAyLjQwNy0xLjYxMloiIGZpbGw9IiNmZmYiLz48L3N2Zz4=";

    const chosenVideo = [
      {
        videoPathMov: "/sites/all/themes/wille/overlay/videos/orla/orla.mov",
        videoPathWebm: "/sites/all/themes/wille/overlay/videos/orla/orla.webm",
        animate: false,
      },
      {
        videoPathMov: "/sites/all/themes/wille/overlay/videos/pig/pig.mov",
        videoPathWebm: "/sites/all/themes/wille/overlay/videos/pig/pig.webm",
        animate: true,
      },
    ];

    let randomIndex = Math.floor(Math.random() * chosenVideo.length);

    let getVideo = chosenVideo[randomIndex];

    const styleSheet2 = document.createElement("style");
    // Create video element
    const videoTag = document.createElement("video");
    // Set video properties
    videoTag.autoplay = true;
    videoTag.muted = true;
    videoTag.loop = true;
    videoTag.playsInline = true;

    // Create source elements for multiple formats
    const sourceWebm = document.createElement("source");
    sourceWebm.src = getVideo.videoPathWebm;
    sourceWebm.type = "video/webm";

    const sourceMov = document.createElement("source");
    sourceMov.src = getVideo.videoPathMov;
    sourceMov.type = "video/quicktime";

    // Append source elements to video tag
    videoTag.appendChild(sourceMov);
    videoTag.appendChild(sourceWebm);

    // Load the video
    videoTag.load();
    videoTag.style.height = "fit-content";
    videoTag.style.bottom = "20px";
    videoTag.style.right = "20px";
    videoTag.style.position = "absolute";
    videoTag.style.cursor = "pointer";
    videoTag.style.pointerEvents = "auto";

    // Create animated div
    const animatedDiv = document.createElement("div");
    animatedDiv.style.width = "100%";
    animatedDiv.style.height = "100%";
    animatedDiv.style.position = "absolute";
    animatedDiv.style.bottom = "0";
    // Append the video to the body

    // Add animation to the animatedDiv
    const animationName = "moveRightToLeft";
    if (getVideo.animate) {
      videoTag.style.bottom = "-20px";

      styleSheet2.innerText = `
        @-webkit-keyframes ${animationName} {
            0% { -webkit-transform: translateX(100%); transform: translateX(100%); }
            100% { -webkit-transform: translateX(-100%); transform: translateX(-100%); }
        }
        @keyframes ${animationName} {
            0% { transform: translateX(100%); }
            100% { transform: translateX(-100%); }
        }

        .animated-div {
          animation: ${animationName} 13s linear infinite;
        }

        .video-tag {
          max-height: 450px;
        }

        /* Media query for mobile view */
        @media (max-width: 768px) {
          .video-tag {
            max-height: 300px;
          }
          .animated-div {
            animation: ${animationName} 7s linear infinite;  /* Adjusted animation speed for mobile */
          }
        }
      `;
    } else {
      styleSheet2.innerText = `
      .video-tag {
        height: fit-content;
        max-height: 550px;
        bottom: 20px;
        right: 20px;
        position: absolute;
        cursor: pointer;
        pointer-events: auto;
      }
      /* Media query for mobile view */
      @media (max-width: 768px) {
        .video-tag {
          max-height: 360px;
        }
      }
    `;
    }
    videoTag.classList.add("video-tag");
    animatedDiv.classList.add("animated-div");
    document.head.appendChild(styleSheet2);

    videoTag.oncanplaythrough = function () {
      videoTag.play();
    };

    animatedDiv.appendChild(videoTag);

    videoTag.addEventListener("click", function () {
      window.location.href = "https://www.orlaafstemning.dk";
    });

    // Create close button
    const closeButton = document.createElement("button");
    closeButton.style.backgroundImage = `url('data:image/svg+xml;base64,${closeSvg}')`;
    closeButton.style.backgroundSize = "16px 15px";
    closeButton.style.backgroundRepeat = "no-repeat";
    closeButton.style.backgroundPosition = "center";
    closeButton.style.width = "25px";
    closeButton.style.height = "25px";
    closeButton.style.border = "none";
    closeButton.style.backgroundColor = "#007FC5";
    closeButton.style.border = "1px solid white";
    closeButton.style.cursor = "pointer";
    closeButton.style.position = "absolute";
    closeButton.style.bottom = "15px";
    closeButton.style.right = "20px";
    closeButton.style.borderRadius = "50%";
    closeButton.style.pointerEvents = "auto";

    // Add event listener to the close button to remove the parentDiv
    closeButton.addEventListener("click", function () {
      document.body.removeChild(parentDiv);

      document.head.removeChild(styleSheet);
    });

    const parentDiv = document.createElement("div");
    parentDiv.style.position = "fixed";
    parentDiv.style.height = "100%";
    parentDiv.style.width = "100%";
    parentDiv.style.zIndex = "10000";
    parentDiv.style.left = "0";
    parentDiv.style.top = "0";
    parentDiv.style.pointerEvents = "none";

    parentDiv.appendChild(animatedDiv);
    parentDiv.appendChild(closeButton);

    document.body.appendChild(parentDiv);

    const styleSheet = document.createElement("style");
    styleSheet.innerText = `
      @keyframes ${animationName} {
        0% { transform: translateX(100%); }
        100% { transform: translateX(-100%); }
      }
      `;

    document.head.appendChild(styleSheet);
  });
})();
